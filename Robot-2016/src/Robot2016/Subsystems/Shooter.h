#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Shooter: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<cougar::CougarSpeedController> bottomRoller;
	std::shared_ptr<cougar::CougarSpeedController> topRoller;
	std::shared_ptr<CANTalon> angleMotor;
	std::shared_ptr<AnalogPotentiometer> potentiometer;

	//The following variables are used for the 1D motion mapping of the shooter angle.
	double timeElapsed, goal_pos, setpoint_pos, setpoint_vel, setpoint_acc, config_max_vel, config_max_acc, next_state_pos,
	next_state_vel, next_state_acc, last_error_, error_sum_, kp_, ki_, kd_, kv_, ka_, last_error;
	bool reset_;

public:
	Shooter();
	void InitDefaultCommand();
	double calculate(double position);
};

#endif
