#ifndef Intake_H
#define Intake_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Intake: public Subsystem
{
private:
	std::shared_ptr<cougar::CougarSpeedController> roller;
	std::shared_ptr<DigitalInput> ballSwitch;
	std::shared_ptr<DoubleSolenoid> angleAirCylinder;
	std::shared_ptr<DoubleSolenoid> liftAirCylinder;
	std::shared_ptr<Compressor> compressor;

public:
	Intake();
	void InitDefaultCommand();
	void setAngleAirCylinder(enum DoubleSolenoid::Value position);
	void setLiftAirCylinder(enum DoubleSolenoid::Value position);
	enum DoubleSolenoid::Value getAngleAirCylinderValue();
	enum DoubleSolenoid::Value getLiftAirCylinderValue();
	void setRoller(double value);
	bool getPressureSwitchValue();
};

#endif
