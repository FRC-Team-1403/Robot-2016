#ifndef Intake_H
#define Intake_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include <memory>

class Intake: public Subsystem
{
public:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<cougar::CougarSpeedController> roller;
	std::shared_ptr<DigitalInput> ballSwitch;
	//std::shared_ptr<Ultrasonic> ultrasonic;
	std::shared_ptr<DoubleSolenoid> angleAirCyclinder;
	std::shared_ptr<DoubleSolenoid> liftAirCyclinder;
	std::shared_ptr<Compressor> compressor;

	Intake();
	void InitDefaultCommand();
};

#endif
