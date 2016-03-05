#ifndef Intake_H
#define Intake_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Intake: public Subsystem
{
public:
	std::shared_ptr<cougar::CougarSpeedController> roller;
	std::shared_ptr<DigitalInput> ballSwitch;
	std::shared_ptr<DoubleSolenoid> rollersAirCylinder;
	std::shared_ptr<Solenoid> triggerAirCylinder;

	Intake();
	void InitDefaultCommand();

	void stop();
	void liftRollersAirCylinder();
	void dropRollersAirCylinder();
	void liftTriggerAirCylinder();
	void dropTriggerAirCylinder();
	bool getTriggerAirCylinderValue();
	enum DoubleSolenoid::Value getRollersAirCylinderValue();
	void setRoller(double value);
	bool getBallSwitchValue();
};

#endif
