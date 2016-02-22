#ifndef Intake_H
#define Intake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Intake: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<cougar::CougarSpeedController> roller;
	std::shared_ptr<DigitalInput> ballSwitch;
	std::shared_ptr<Ultrasonic> ultrasonic;
	std::shared_ptr<Solenoid> angleAirCyclinder;
	std::shared_ptr<Solenoid> liftAirCyclinder;
	std::shared_ptr<Compressor> compressor;
public:
	Intake();
	void InitDefaultCommand();
	void setAngleAirCyclinder(bool position);
	void setLiftAirCyclinder(bool position);
};

#endif
