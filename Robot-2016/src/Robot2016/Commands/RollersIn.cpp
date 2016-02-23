#include "RollersIn.h"
#include "../Robot.h"

RollersIn::RollersIn()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void RollersIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RollersIn::Execute()
{
	Robot::intake->roller->Set(1);
}

// Make this return true when this Command no longer needs to run execute()
bool RollersIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RollersIn::End()
{
	Robot::intake->roller->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollersIn::Interrupted()
{
	End();
}
