#include "StopAllOperator.h"
#include "../Robot.h"

StopAllOperator::StopAllOperator()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	cougar::CougarDebug::startMethod("StopAllOperator::StopAllOperator");
	Requires(Robot::intake.get());
	Requires(Robot::shooter.get());
	didGo = false;
	cougar::CougarDebug::startMethod("StopAllOperator::StopAllOperator");
}

// Called just before this Command runs the first time
void StopAllOperator::Initialize()
{
	cougar::CougarDebug::startMethod("StopAllOperator::Initialize");
	didGo = false;
	cougar::CougarDebug::endMethod("StopAllOperator::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void StopAllOperator::Execute()
{
	Robot::intake->stop();
	Robot::shooter->stop();
	didGo = true;
}

// Make this return true when this Command no longer needs to run execute()
bool StopAllOperator::IsFinished()
{
	return didGo;
}

// Called once after isFinished returns true
void StopAllOperator::End()
{
	cougar::CougarDebug::startMethod("StopAllOperator::End");
	cougar::CougarDebug::endMethod("StopAllOperator::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAllOperator::Interrupted()
{
	cougar::CougarDebug::startMethod("StopAllOperator::Interrupted");
	End();
	cougar::CougarDebug::endMethod("StopAllOperator::Interrupted");
}
