#include "RollersOut.h"
#include "../../Robot.h"

RollersOut::RollersOut()
{
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void RollersOut::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RollersOut::Execute()
{
	Robot::intake->setRoller(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool RollersOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RollersOut::End()
{
	Robot::intake->setRoller(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollersOut::Interrupted()
{
	End();
}
