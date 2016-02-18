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
public:
	Shooter();
	void InitDefaultCommand();
};

#endif
