#ifndef ExampleSubsystem_H
#define ExampleSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <memory>
#include "../Commands/ExampleCommand.h"
#include "../RobotMap.h"
#include "../../CougarLib/CougarDebug.h"

class ExampleSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ExampleSubsystem();
	void InitDefaultCommand();
	std::shared_ptr<CANTalon> getTalon() { return talon; }


private:
	std::shared_ptr<CANTalon> talon;
};

#endif
