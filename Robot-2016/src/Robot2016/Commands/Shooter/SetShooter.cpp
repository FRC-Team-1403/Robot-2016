#include "SetShooter.h"
#include "../../Robot.h"

SetShooter::SetShooter(float angle)
{
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void SetShooter::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SetShooter::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SetShooter::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SetShooter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooter::Interrupted()
{

}
