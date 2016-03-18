/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

// TODO Finish debugging for this class.
// Not doing it right now because TrajectoryLib needs to be fixed first.

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(uint32_t leftPort, uint32_t rightPort,
		uint32_t leftPDPSlot, uint32_t rightPDPSlot, std::string name, bool reversed) : Debuggable(name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<SpeedController> tmpLeft(new CougarSpeedController(leftPort, leftPDPSlot, name + "Left"));
	std::shared_ptr<SpeedController> tmpRight(new CougarSpeedController(rightPort, rightPDPSlot, name + "Right"));
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(tmpLeft, tmpRight));
	this->drive_ = tmpDrive;
	this->reverse_ = reversed ? -1 : 1;
	this->configFPID();
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::CougarDrive(uint32_t leftPort1, uint32_t leftPort2,
		uint32_t rightPort1, uint32_t rightPort2,
		uint32_t leftPDPSlot1, uint32_t leftPDPSlot2,
		uint32_t rightPDPSlot1, uint32_t rightPDPSlot2,
		std::string name, bool reversed) : Debuggable(name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<SpeedController> tmpLeft(new CougarSpeedControllerAggregate(leftPort1, leftPort2,
			leftPDPSlot1, leftPDPSlot2, name + "Left"));
	std::shared_ptr<SpeedController> tmpRight(new CougarSpeedControllerAggregate(rightPort1, rightPort2,
				rightPDPSlot1, rightPDPSlot2, name + "Right"));
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(tmpLeft, tmpRight));
	this->drive_ = tmpDrive;
	this->reverse_ = reversed ? -1 : 1;
	this->configFPID();
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right,
		std::string name, bool reversed) : Debuggable(name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(left, right));
	this->drive_ = tmpDrive;
	this->reverse_ = reversed ? -1 : 1;
	this->configFPID();
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::~CougarDrive() {
	CougarDebug::startMethod("CougarDrive::~CougarDrive " + this->GetName());
	CougarDebug::endMethod("CougarDrive::~CougarDrive " + this->GetName());
}

void CougarDrive::Drive(float outputMagnitude, float curve) const {
	this->drive_->Drive(outputMagnitude * reverse_, curve);
}

void CougarDrive::TankDrive(float leftPower, float rightPower, bool squaredInputs /* = false */) {
	this->drive_->TankDrive(leftPower * reverse_, rightPower * reverse_, squaredInputs);
}

void CougarDrive::TankDrive(std::shared_ptr<CougarJoystick> joystick, bool squaredInputs /* = false */) {
	if (CougarConstants::DEFAULT_DRIVE_STATE == CougarConstants::DIRECT_DRIVE) {
		this->TankDrive(joystick->GetStickLeftAxisY(), joystick->GetStickRightAxisY(), squaredInputs);
	} else {
		//TODO
	}
}

void CougarDrive::ArcadeDrive(float magnitude, float curve, bool squaredInputs) {
	if (CougarConstants::DEFAULT_DRIVE_STATE == CougarConstants::DIRECT_DRIVE) {
		this->drive_->ArcadeDrive(magnitude * reverse_, curve * reverse_, squaredInputs);
	} else {
		//TODO
	}
}

void CougarDrive::ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs /* = false */) {
	if (stick == LEFT) {
		this->ArcadeDrive(joystick->GetStickLeftAxisY(), joystick->GetStickLeftAxisX(), squaredInputs);
	} else if (stick == RIGHT) {
		this->ArcadeDrive(joystick->GetStickRightAxisY(), joystick->GetStickRightAxisX(), squaredInputs);
	} else {
		CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
	}
}

void CougarDrive::LockDrive(std::shared_ptr<CougarEncoder> leftEncoder, std::shared_ptr<CougarEncoder> rightEncoder) {
	this->TankDrive(this->calculate(leftEncoder->GetDistance(), this->leftController),this->calculate(rightEncoder->GetDistance(), this->rightController));
}

void CougarDrive::AutomaticDrive(std::shared_ptr<CougarJoystick> joystick, std::shared_ptr<CougarEncoder> leftEncoder, std::shared_ptr<CougarEncoder> rightEncoder) {
	if (joystick->AreZeroSticks()) {
		this->LockDrive(leftEncoder, rightEncoder);
	} else if (joystick->GetButtonStart()) {
		this->configFPID();
		this->leftController.goal_pos = leftEncoder->GetDistance();
		this->rightController.goal_pos = rightEncoder->GetDistance();
		(this->*cougar::CougarDrive::AltDrive())(joystick);
	} else {
		this->configFPID();
		this->leftController.goal_pos = leftEncoder->GetDistance();
		this->rightController.goal_pos = rightEncoder->GetDistance();
		(this->*cougar::CougarDrive::DefaultDrive())(joystick);
	}
}

void CougarDrive::InternalTankDrive(std::shared_ptr<CougarJoystick> joystick) {
	this->TankDrive(joystick);
}

void CougarDrive::InternalArcadeDrive(std::shared_ptr<CougarJoystick> joystick) {
	this->ArcadeDrive(joystick);
}

CougarDrive::drive_func CougarDrive::DefaultDrive() {
	switch (CougarConstants::JOYSTICK_DRIVE_STATE) {
	case CougarConstants::ARCADE_DRIVE:
		return &cougar::CougarDrive::InternalArcadeDrive;
	case CougarConstants::TANK_DRIVE:
		return &cougar::CougarDrive::InternalTankDrive;
	default:
		// This is a problem
		return nullptr;
	}
}

CougarDrive::drive_func CougarDrive::AltDrive() {
	switch (CougarConstants::JOYSTICK_DRIVE_STATE) {
	case CougarConstants::ARCADE_DRIVE:
		return &cougar::CougarDrive::InternalTankDrive;
	case CougarConstants::TANK_DRIVE:
		return &cougar::CougarDrive::InternalArcadeDrive;
	default:
		return nullptr;
	}
}

void CougarDrive::SetSensitivity(float sensitivity) {
	CougarDebug::startMethod("CougarDrive::SetSensitivity");
	this->drive_->SetSensitivity(sensitivity);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "sensitivity set to " + std::to_string(sensitivity));
	CougarDebug::endMethod("CougarDrive::SetSensitivity");
}

void CougarDrive::SetMaxOutput(double maxOutput) {
	CougarDebug::startMethod("CougarDrive::SetMaxOutput");
	this->drive_->SetMaxOutput(maxOutput);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "max output set to " + std::to_string(maxOutput));
	CougarDebug::endMethod("CougarDrive::SetMaxOutput");
}

void CougarDrive::SetExpiration(float timeout) {
	CougarDebug::startMethod("CougarDrive::SetExpiration");
	this->drive_->SetExpiration(timeout);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "expiration set to " + std::to_string(timeout));
	CougarDebug::endMethod("CougarDrive::SetExpiration");
}

float CougarDrive::GetExpiration() const {
	return this->drive_->GetExpiration();
}

bool CougarDrive::IsAlive() const {
	return this->drive_->IsAlive();
}

void CougarDrive::Stop() {
	this->drive_->StopMotor();
}

bool CougarDrive::IsSafetyEnabled() const {
	return this->drive_->IsSafetyEnabled();
}

void CougarDrive::SetSafetyEnabled(bool enabled) {
	CougarDebug::startMethod("CougarDrive::SetSafetyEnabled");
	this->drive_->SetSafetyEnabled(enabled);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "safety set to " + std::to_string(enabled));
	CougarDebug::endMethod("CougarDrive::SetSafetyEnabled");
}
std::string CougarDrive::GetName() const {
	return this->name_;
}

const char *CougarDrive::GetCName() const {
	return this->name_.c_str();
}

std::string CougarDrive::toString() {
	std::string str = "CougarDrive " + this->name_ + "\n";
	return str;
}

// TODO
std::string CougarDrive::dumpState() {
	std::string str = this->toString();
	return str;
}

std::shared_ptr<RobotDrive> CougarDrive::GetDrive() {
	return this->drive_;
}

void CougarDrive::configFPID() {
	leftController.last_error_ = 0;
	leftController.kp_ = 1.5;
	leftController.config_max_acc = 30;
	leftController.config_max_vel = 9;
	leftController.setpoint_vel = 0;
	leftController.setpoint_acc = 0;
	leftController.next_state_vel = 0;
	leftController.goal_pos = 0;
	leftController.error_sum_ = 0;
	leftController.setpoint_pos = 0;
	leftController.kd_ = 0.1;
	leftController.kv_ = 1 / leftController.config_max_vel;
	leftController.timeElapsed = 0;
	leftController.next_state_pos = 0;
	leftController.reset_ = 0;
	leftController.ki_ = 0;
	leftController.next_state_acc = 0;
	leftController.ka_ = 1 / leftController.config_max_acc;

	rightController.last_error_ = 0;
	rightController.kp_ = 1.5;
	rightController.config_max_acc = 30;
	rightController.config_max_vel = 9;
	rightController.setpoint_vel = 0;
	rightController.setpoint_acc = 0;
	rightController.next_state_vel = 0;
	rightController.goal_pos = 0;
	rightController.error_sum_ = 0;
	rightController.setpoint_pos = 0;
	rightController.kd_ = 0.1;
	rightController.kv_ = 1 / leftController.config_max_vel;
	rightController.timeElapsed = 0;
	rightController.next_state_pos = 0;
	rightController.reset_ = 0;
	rightController.ki_ = 0;
	rightController.next_state_acc = 0;
	rightController.ka_ = 1 / leftController.config_max_acc;

	angleController.last_error_ = 0;
	angleController.kp_ = 1.5;
	angleController.config_max_acc = 30;
	angleController.config_max_vel = 9;
	angleController.setpoint_vel = 0;
	angleController.setpoint_acc = 0;
	angleController.next_state_vel = 0;
	angleController.goal_pos = 0;
	angleController.error_sum_ = 0;
	angleController.setpoint_pos = 0;
	angleController.kd_ = 0.1;
	angleController.kv_ = 1 / leftController.config_max_vel;
	angleController.timeElapsed = 0;
	angleController.next_state_pos = 0;
	angleController.reset_ = 0;
	angleController.ki_ = 0;
	angleController.next_state_acc = 0;
	angleController.ka_ = 1 / leftController.config_max_acc;
}

//variables that are not local within this method: setpoint_pos, setpoint_vel, setpoint_acc, goal_pos, timeElapsed, config_max_acc
double CougarDrive::calculate (double position, FPID_CONTROLLER controller){ //position is the encoder output; program returns motor value from -1 to 1
	controller.timeElapsed = Timer::GetFPGATimestamp(); //sets timeElapsed to current time. The Timer should start at the beginning of any command using this method.
	if(std::abs(controller.setpoint_pos - controller.goal_pos) < 0.001 && std::abs(controller.setpoint_vel) < .01){ //This will run when you're very close to your goal.
		controller.setpoint_pos = controller.goal_pos; //goal_pos is the ultimate goal you want to achieve at the end of the command that you're running this method in.
		//setpoint_pos is where you want the robot to be the next time this method is called (in 1/20th of a second)
		//if the setpoint and the goal are within .001 of each other (meaning they're practically the same at this point), make the setpoint the same value as the goal.
		controller.setpoint_vel = 0; controller.setpoint_acc = 0; //By the end of your motion, the velocity and the acceleration should both be zero, so if the velocity setpoint is less than .01, set the setpoint to 0.
	}
	else{ //This will run when you're not at your goal yet.
		double distanceToGo = controller.goal_pos - controller.setpoint_pos; //distanceToGo represents how far you must go after this cycle of the method.
		double current_vel = controller.setpoint_vel; //current_vel is the same as the velocity setpoint (what velocity you want to be going at by the end of this cycle)
		double current_vel2 = current_vel * current_vel; //current_vel2 is the square of the velocity setpoint.
		bool inverted = false;
		if(distanceToGo < 0){ //If the robot needs to go backwards...
			inverted = true;
			distanceToGo *= -1; //...set the distanceToGo and velocity to negative.
			current_vel *= -1;
		}
		//config_max_acc is a robot specific constant.
		//max_reachable_vel represents the highest velocity the robot can move at while still being able to slow down in time and stop precisely at the goal. It is found with the calculation below.
		double max_reachable_vel = current_vel2/2.0 + controller.config_max_acc * distanceToGo; //in math terms: vmax = (v^2)/2 + a * x
		double min_reachable_vel = current_vel2/2.0 - controller.config_max_acc * distanceToGo; //vmin = (v^2)/2 - a * x
		double cruise_vel = current_vel; //cruise_vel represents the speed that we want the robot to speed up to and maintain throughout the motion.
		//For the majority of the motion, the robot will be at the cruise velocity. The only times the cruise velocity will not be equal to the current velocity
		//are at the beginning during speed up and the end during slow down.
		if(min_reachable_vel < 0 || cruise_vel < 0){ //if the robot is going backwards...
			//config_max_vel is a robot specific constant. max_reachable_vel was calculated above.
			//The cruise_vel will be the one used for processing below.
			//We want to set cruise_vel to the square root of max_reachable_vel if we can, but if that's higher than the robot's max velocity, we have to use the robot's max velocity instead.
			//The line of code below picks whichever is smaller and uses that as the cruise velocity.
			cruise_vel = fmin(controller.config_max_vel, sqrt(max_reachable_vel));

		}

		//The following is all creating position and time variables using physics formulas.

		//The purpose of calculating the following four variables is for using them for finding the 5th and 6th variables here.
		double t_start = (cruise_vel - current_vel)/controller.config_max_acc;
		//t_start represents the time spent in the acceleration phase.
		//physics formula: a = change in v/change in t -> t-0 = (vf-vi)/a, final velocity is the cruise velocity, initial velocity is the current velocity

		double x_start = (current_vel * t_start) + .5 * controller.config_max_acc * t_start * t_start;
		//x_start represents the distance remaining in the acceleration phase.
		//physics formula: x = vi*t + (1/2)at^2
		//The equation represents the accelerating part of the motion profile. To find the end position of that part, we plug in the full time it takes to accelerate, calculated above.

		double t_end = std::abs(cruise_vel/controller.config_max_acc);
		//t_end represents the amount of time it takes to decelerate.
		//physics formula: a = v/t -> t = change in v/a, change in v = cruise velocity - 0

		double x_end = cruise_vel * t_end - .5 * controller.config_max_acc * t_end * t_end;
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

		if(t_start >= controller.timeElapsed){ //This runs when the robot is accelerating.
			controller.next_state_pos = current_vel * controller.timeElapsed + .5 * controller.config_max_acc * controller.timeElapsed * controller.timeElapsed; //x = vi*t + (1/2)at^2
			controller.next_state_vel = current_vel + controller.config_max_acc * controller.timeElapsed; //v = vi + at
			controller.next_state_acc = controller.config_max_acc; //a = max
		}
		else if(t_start + t_cruise >= controller.timeElapsed){ //This runs when the robot is cruising.
			controller.next_state_pos = x_start + cruise_vel * (controller.timeElapsed - t_start); //xf = xi + vt
			controller.next_state_vel = cruise_vel;
			controller.next_state_acc = 0;
		}
		else if(t_start + t_cruise + t_end >= controller.timeElapsed){ //This runs when the robot is decelerating.
			double delta_t = controller.timeElapsed - t_start - t_cruise; //delta_t represents the time spent in the deceleration phase.
			controller.next_state_pos = x_start + x_cruise + cruise_vel * delta_t - .5 * controller.config_max_acc * delta_t * delta_t; //x = (1/2)at^2
			controller.next_state_vel = cruise_vel - controller.config_max_acc * delta_t; //v = vi - at
			controller.next_state_acc = -1 * (controller.config_max_acc); //slow down as fast as possible
		}
		else{ //Probably shouldn't happen, but just in case
			controller.next_state_pos = distanceToGo;
			controller.next_state_vel = 0;
			controller.next_state_acc = 0;
		}
		if(inverted){ //Inverted will be true if distanceToGo is negative. The following statements change the direction of the movement.
			controller.next_state_pos = -controller.next_state_pos;
			controller.next_state_vel = -controller.next_state_vel;
			controller.next_state_acc = -controller.next_state_acc;
		}

		//The setpoint variables represent the where the robot wants to by the beginning of next cycle.
		controller.setpoint_pos = controller.setpoint_pos + controller.next_state_pos;
		controller.setpoint_vel = controller.next_state_vel;
		controller.setpoint_acc = controller.next_state_acc;
	}
	double error = controller.setpoint_pos - position; //Position is the current encoder value, a passed parameter. error represents the distance between the robot's current position
	//and where it wants to be by the end of the cycle.
	if(controller.reset_){
		controller.reset_ = false;
		controller.last_error_ = error;
		controller.error_sum_ = 0;
	}

	//kp_, ki_, and kd_ are the robot specific PID constants. Output is determined by the sum of the PID equations.
	double output = controller.kp_ * error + controller.kd_ * ((error - controller.last_error_)/controller.timeElapsed - controller.setpoint_vel) + (controller.kv_ * controller.setpoint_vel + controller.ka_ * controller.setpoint_acc);
	if(output < 1 && output > -1){
		controller.error_sum_ += error * controller.timeElapsed;
	}
	output += controller.ki_ * controller.error_sum_;

	controller.last_error_ = error;
	return output;
}

} /* namespace cougar */
