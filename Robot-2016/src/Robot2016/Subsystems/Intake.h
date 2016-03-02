#ifndef Intake_H
#define Intake_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSolenoid.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarDoubleSolenoid.h"

#include <memory>

class Intake: public Subsystem
{
private:
	std::shared_ptr<cougar::CougarSpeedController> roller;
	std::shared_ptr<DigitalInput> ballSwitch;
	std::shared_ptr<cougar::CougarDoubleSolenoid> rollersAirCylinder;
	std::shared_ptr<cougar::CougarSolenoid> triggerAirCylinder;

public:
	Intake();
	void InitDefaultCommand();

	void stop();
	void liftRollersAirCylinder();
	void dropRollersAirCylinder();
	void liftTriggerAirCylinder();
	void dropTriggerAirCylinder();
	bool getTriggerAirCylinderValue();
	enum cougar::CougarDoubleSolenoid::Value getRollersAirCylinderValue();
	void setRoller(double value);
	bool getBallSwitchValue();
};

#endif
