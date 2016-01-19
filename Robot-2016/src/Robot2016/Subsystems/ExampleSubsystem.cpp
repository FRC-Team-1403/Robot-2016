#include "ExampleSubsystem.h"


ExampleSubsystem::ExampleSubsystem() :
		Subsystem("ExampleSubsystem")
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleSubsystem constructor running");
	talon = RobotMap::talon;
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleSubsystem constructor finished");
}

void ExampleSubsystem::InitDefaultCommand()
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "Setting ExampleSubsystem InitDefaultCommand running");
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ExampleCommand());
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "Setting ExampleSubsystem InitDefaultCommand running finished");

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
