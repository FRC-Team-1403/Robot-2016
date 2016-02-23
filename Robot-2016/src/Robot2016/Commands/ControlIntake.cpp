#include "ControlIntake.h"
#include "../Robot.h"

ControlIntake::ControlIntake()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void ControlIntake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ControlIntake::Execute()
{
	Robot::intake->roller->Set(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisX());
}

// Make this return true when this Command no longer needs to run execute()
bool ControlIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ControlIntake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlIntake::Interrupted()
{

}
