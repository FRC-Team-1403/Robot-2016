#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Shooter: public Subsystem
{
public:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<CANTalon> bottomRoller;
	std::shared_ptr<CANTalon> topRoller;
	std::shared_ptr<CANTalon> angleMotor;
	//std::shared_ptr<NetworkTable> cameraTable;

	//std::shared_ptr<AnalogPotentiometer> potentiometer; the potentiometer is connected directly to the CANTalon

	//The following variables are used for the 1D motion mapping of the shooter angle.
	/* timeElapsed, goal_pos, setpoint_pos, setpoint_vel, setpoint_acc, config_max_vel, config_max_acc, next_state_pos,
	next_state_vel, next_state_acc, last_error_, error_sum_, kp_, ki_, kd_, kv_, ka_, last_error;
	bool reset_;*/

	Shooter();
	void InitDefaultCommand();

	//methods for retrieving private values
	double getPotentiometer();
	//double getGoalPos();
	//void setGoalPos(double goal);
	void setAngleMotor(double velocity);
	void setTopRoller(double velocity);
	void setBottomRoller(double velocity);

	//std::shared_ptr<NetworkTable> getCameraTable();
	//double getCameraCenterX();
	//double getCameraCenterY();

	//double calculate(double position);
};

#endif
