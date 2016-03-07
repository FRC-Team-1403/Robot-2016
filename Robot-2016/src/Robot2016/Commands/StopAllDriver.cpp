#include "StopAllDriver.h"
#include "../Robot.h"

StopAllDriver::StopAllDriver()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	cougar::CougarDebug::startMethod("StopAllDriver::StopAllDriver");
	Requires(Robot::driveTrain.get());
	didGo = false;
	cougar::CougarDebug::startMethod("StopAllDriver::StopAllDriver");
}

// Called just before this Command runs the first time
void StopAllDriver::Initialize()
{
	cougar::CougarDebug::startMethod("StopAllDriver::Initialize");
	cougar::CougarDebug::endMethod("StopAllDriver::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void StopAllDriver::Execute()
{
	Robot::driveTrain->stop();
	didGo = true;
}

// Make this return true when this Command no longer needs to run execute()
bool StopAllDriver::IsFinished()
{
	return didGo;
}

// Called once after isFinished returns true
void StopAllDriver::End()
{
	cougar::CougarDebug::startMethod("StopAllDriver::End");
	cougar::CougarDebug::endMethod("StopAllDriver::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAllDriver::Interrupted()
{
	cougar::CougarDebug::startMethod("StopAllDriver::Interrupted");
	End();
	cougar::CougarDebug::endMethod("StopAllDriver::Interrupted");
}
