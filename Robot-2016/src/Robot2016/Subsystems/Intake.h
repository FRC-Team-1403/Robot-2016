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
	std::shared_ptr<DoubleSolenoid> rollersAirCylinder;
	std::shared_ptr<DoubleSolenoid> triggerAirCylinder;
	std::shared_ptr<DigitalInput> limitSwitch;
	//std::shared_ptr<Compressor> compressor;

public:
	Intake();
	void InitDefaultCommand();
	void liftRollersAirCylinder();
	void dropRollersAirCylinder();
	void liftTriggerAirCylinder();
	void dropTriggerAirCylinder();
	enum DoubleSolenoid::Value getTriggerAirCylinderValue();
	enum DoubleSolenoid::Value getRollersAirCylinderValue();
	void setRoller(double value);
	bool getPressureSwitchValue();
	bool getLimitSwitchValue();
};

#endif
