#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/AimWithJoystick.h"

Shooter::Shooter() :
		Subsystem("ExampleSubsystem")
{
	bottomRoller = RobotMap::shooterRollerBottom;
	topRoller = RobotMap::shooterRollerTop;
	angleMotor = RobotMap::shooterAngleMotor;
	cameraTable = NetworkTable::GetTable("SmartDashboard");
	//potentiometer = RobotMap::shooterPotentiometer;

	//These are used by the calculate method. Their values will change.
	goal_pos = 0; //this will be set by the command that calculates the angle using the projectile motion algorithms.
	setpoint_pos = 0;
	setpoint_vel = 0;
	setpoint_acc = 0;
	next_state_pos = 0;
	next_state_vel = 0;
	next_state_acc = 0;
	last_error_ = 0;
	error_sum_ = 0;
	reset_ = false;

	//These are robot specific constants.
	config_max_vel = 0;
	config_max_acc = 0;
	kp_ = 0;
	ki_ = 0;
	kd_ = 0;
	kv_ = 0;
	ka_ = 0;
}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new AimWithJoystick());
}

double Shooter::getPotentiometer() {
	return angleMotor->GetEncPosition();
}

double Shooter::getGoalPos() {
	return goal_pos;
}

void Shooter::setGoalPos(double goal) {
	goal_pos = goal;
}

void Shooter::setAngleMotor(double velocity) {
	angleMotor->Set(velocity);
}

double Shooter::getCameraCenterX() {
	return cameraTable->GetNumber("centerX");
}

double Shooter::getCameraCenterY() {
	return cameraTable->GetNumber("centerY");
}

//This method is used for the 1D motion mapping of the shooter.
double Shooter::calculate (double position){ //position is the encoder output; program returns motor value from -1 to 1
		timeElapsed = Timer::GetFPGATimestamp(); //sets timeElapsed to current time. The Timer should start at the beginning of any command using this method.
		if(std::abs(setpoint_pos - goal_pos) < 0.001 && std::abs(setpoint_vel) < .01){ //This will run when you're very close to your goal.
			setpoint_pos = goal_pos; //goal_pos is the ultimate goal you want to achieve at the end of the command that you're running this method in.
			//setpoint_pos is where you want the robot to be the next time this method is called (in 1/20th of a second)
			//if the setpoint and the goal are within .001 of each other (meaning they're practically the same at this point), make the setpoint the same value as the goal.
			setpoint_vel = 0; setpoint_acc = 0; //By the end of your motion, the velocity and the acceleration should both be zero, so if the velocity setpoint is less than .01, set the setpoint to 0.
		}
		else{ //This will run when you're not at your goal yet.
			double distanceToGo = goal_pos - setpoint_pos; //distanceToGo represents how far you must go after this cycle of the method.
			double current_vel = setpoint_vel; //current_vel is the same as the velocity setpoint (what velocity you want to be going at by the end of this cycle)
			double current_vel2 = current_vel * current_vel; //current_vel2 is the square of the velocity setpoint.
			bool inverted = false;
			if(distanceToGo < 0){ //If the robot needs to go backwards...
				inverted = true;
				distanceToGo *= -1; //...set the distanceToGo and velocity to negative.
				current_vel *= -1;
			}
			//config_max_acc is a robot specific constant.
			//max_reachable_vel represents the highest velocity the robot can move at while still being able to slow down in time and stop precisely at the goal. It is found with the calculation below.
			double max_reachable_vel = current_vel2/2.0 + config_max_acc * distanceToGo; //in math terms: vmax = (v^2)/2 + a * x
			double min_reachable_vel = current_vel2/2.0 - config_max_acc * distanceToGo; //vmin = (v^2)/2 - a * x
			double cruise_vel = current_vel; //cruise_vel represents the speed that we want the robot to speed up to and maintain throughout the motion.
			//For the majority of the motion, the robot will be at the cruise velocity. The only times the cruise velocity will not be equal to the current velocity
			//are at the beginning during speed up and the end during slow down.
			if(min_reachable_vel < 0 || cruise_vel < 0){ //if the robot is going backwards...
				//config_max_vel is a robot specific constant. max_reachable_vel was calculated above.
				//The cruise_vel will be the one used for processing below.
				//We want to set cruise_vel to the square root of max_reachable_vel if we can, but if that's higher than the robot's max velocity, we have to use the robot's max velocity instead.
				//The line of code below picks whichever is smaller and uses that as the cruise velocity.
				cruise_vel = fmin(config_max_vel, sqrt(max_reachable_vel));

			}

			//The following is all creating position and time variables using physics formulas.

			//The purpose of calculating the following four variables is for using them for finding the 5th and 6th variables here.
			double t_start = (cruise_vel - current_vel)/config_max_acc;
			//t_start represents the time spent in the acceleration phase.
			//physics formula: a = change in v/change in t -> t-0 = (vf-vi)/a, final velocity is the cruise velocity, initial velocity is the current velocity

			double x_start = (current_vel * t_start) + .5 * config_max_acc * t_start * t_start;
			//x_start represents the distance remaining in the acceleration phase.
			//physics formula: x = vi*t + (1/2)at^2
			//The equation represents the accelerating part of the motion profile. To find the end position of that part, we plug in the full time it takes to accelerate, calculated above.

			double t_end = std::abs(cruise_vel/config_max_acc);
			//t_end represents the amount of time it takes to decelerate.
			//physics formula: a = v/t -> t = change in v/a, change in v = cruise velocity - 0

			double x_end = cruise_vel * t_end - .5 * config_max_acc * t_end * t_end;
			//x_end represents the position where cruising ends and deceleration starts.
			//physics formula: x = vi*t + (1/2)at^2. During the deceleration phase, config_max_acc is negative.

			double x_cruise = fmax(0.0, (distanceToGo - x_start - x_end));
			//x_cruise represents the distance remaining during the cruise phase. It is found by subtracting the distances of the accel and decel phases from the distance to the end.
			//If the value is negative, then that means the cruise phase is already over, so it is set to 0.

			double t_cruise = std::abs(x_cruise/cruise_vel);
			//t_cruise represents the total time the cruise phase lasts.

			//The following if-else block determines what phase of the motion profile the robot is in and tells the robot what to do.
			//next_state_pos represents the difference between the current position and where you want to be by the next cycle.
			//next_state_vel represents the speed you want to be at by next cycle.
			//next_state_acc represents the acceleration you want to be at by next cycle.

			if(t_start >= timeElapsed){ //This runs when the robot is accelerating.
				next_state_pos = current_vel * timeElapsed + .5 * config_max_acc * timeElapsed * timeElapsed; //x = vi*t + (1/2)at^2
				next_state_vel = current_vel + config_max_acc * timeElapsed; //v = vi + at
				next_state_acc = config_max_acc; //a = max
			}
			else if(t_start + t_cruise >= timeElapsed){ //This runs when the robot is cruising.
				next_state_pos = x_start + cruise_vel * (timeElapsed - t_start); //xf = xi + vt
				next_state_vel = cruise_vel;
				next_state_acc = 0;
			}
			else if(t_start + t_cruise + t_end >= timeElapsed){ //This runs when the robot is decelerating.
				double delta_t = timeElapsed - t_start - t_cruise; //delta_t represents the time spent in the deceleration phase.
				next_state_pos = x_start + x_cruise + cruise_vel * delta_t - .5 * config_max_acc * delta_t * delta_t; //x = (1/2)at^2
				next_state_vel = cruise_vel - config_max_acc * delta_t; //v = vi - at
				next_state_acc = -1 * (config_max_acc); //slow down as fast as possible
			}
			else{ //Probably shouldn't happen, but just in case
				next_state_pos = distanceToGo;
				next_state_vel = 0;
				next_state_acc = 0;
			}
			if(inverted){ //Inverted will be true if distanceToGo is negative. The following statements change the direction of the movement.
				next_state_pos = -next_state_pos;
				next_state_vel = -next_state_vel;
				next_state_acc = -next_state_acc;
			}

			//The setpoint variables represent the where the robot wants to by the beginning of next cycle.
			setpoint_pos = setpoint_pos + next_state_pos;
			setpoint_vel = next_state_vel;
			setpoint_acc = next_state_acc;
		}
		double error = setpoint_pos - position; //Position is the current encoder value, a passed parameter. error represents the distance between the robot's current position
		//and where it wants to be by the end of the cycle.
		if(reset_){
			reset_ = false;
			last_error_ = error;
			error_sum_ = 0;
		}

		//kp_, ki_, and kd_ are the robot specific PID constants. Output is determined by the sum of the PID equations.
		double output = kp_ * error + kd_ * ((error - last_error_)/timeElapsed - setpoint_vel) + (kv_ * setpoint_vel + ka_ * setpoint_acc);
		if(output < 1 && output > -1){
			error_sum_ += error * timeElapsed;
		}
		output += ki_ * error_sum_;

		last_error_ = error;
		return output;
	}

// Put methods for controlling this subsystem
// here. Call these from Commands.
