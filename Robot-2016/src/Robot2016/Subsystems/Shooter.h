#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Shooter: public Subsystem
{
public:
	Shooter();
	void InitDefaultCommand();

	void stop();
	double getPotentiometer();
	void setAngleMotor(double position);
	void setTopRoller(double velocity);
	void setBottomRoller(double velocity);
	int getAngleMotorDistance();
	int getAngleMotorVelocity();
	int getTopRollerDistance();
	int getBottomRollerDistance();
	int getTopRollerVelocity();
	int getBottomRollerVelocity();

	std::shared_ptr<CANTalon> bottomRoller;
	std::shared_ptr<CANTalon> topRoller;
	std::shared_ptr<CANTalon> angleMotor;

};

#endif
