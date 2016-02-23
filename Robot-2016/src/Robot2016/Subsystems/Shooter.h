#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Shooter: public Subsystem
{
public:
	std::shared_ptr<CANTalon> bottomRoller;
	std::shared_ptr<CANTalon> topRoller;
	std::shared_ptr<CANTalon> angleMotor;

	Shooter();
	void InitDefaultCommand();

	double getPotentiometer();
	void setAngleMotor(double velocity);
	void setTopRoller(double velocity);
	void setBottomRoller(double velocity);
};

#endif
