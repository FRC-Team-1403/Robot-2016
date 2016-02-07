#include "ExampleCommand.h"
#include "../Robot.h"

ExampleCommand::ExampleCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand constructor finished");
	Requires(Robot::exampleSubsystem.get());
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand constructor finished");
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize()
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand initializing running");
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute()
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand execute starting");
	std::shared_ptr<CANTalon> tmpTalon = Robot::exampleSubsystem->getTalon();
	std::string message = "Got talon at address ";
	int isReal = (int)tmpTalon.get();
	message = message + std::to_string(isReal);
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, message.c_str());
	std::shared_ptr<cougar::CougarJoystick> tmpJoy = Robot::oi->GetJoystick();
	message = "Got joystick at address ";
	int isReal2 = (int)tmpJoy.get();
	message = message + std::to_string(isReal2);
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, message.c_str());
	if (isReal != 0 && isReal2 != 0) {
		Robot::exampleSubsystem->getTalon()->Set(Robot::oi->GetJoystick()->GetStickLeftAxisY());
	} else {
		if (isReal == 0) {
			cougar::CougarDebug::debugPrinter(cougar::CougarDebug::ISSUE, "Talon is a null pointer");
		}
		if (isReal2 == 0) {
			cougar::CougarDebug::debugPrinter(cougar::CougarDebug::ISSUE, "Joystick is a null pointer");
		}
	}
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand execute finishing");

}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ExampleCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted()
{

}
