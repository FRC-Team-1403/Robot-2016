#include "StopAllOperator.h"
#include "../Robot.h"

StopAllOperator::StopAllOperator()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void StopAllOperator::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StopAllOperator::Execute()
{
	Robot::intake->stop();
	Robot::shooter->stop();
}

// Make this return true when this Command no longer needs to run execute()
bool StopAllOperator::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void StopAllOperator::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAllOperator::Interrupted()
{
	End();
}
