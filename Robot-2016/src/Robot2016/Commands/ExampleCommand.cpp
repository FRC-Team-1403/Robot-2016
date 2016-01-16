#include "ExampleCommand.h"
#include "../Robot.h"

ExampleCommand::ExampleCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	Requires(Robot::exampleSubsystem.get());
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize()
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "ExampleCommand initializing running");
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute()
{
	Robot::exampleSubsystem->getMotor()->Set(Robot::oi->GetJoystick()->GetStickLeftAxisY());
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
