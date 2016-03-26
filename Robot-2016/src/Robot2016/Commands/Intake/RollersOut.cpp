#include "RollersOut.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


RollersOut::RollersOut() :
	cougar::CougarCommand("RollersOut", Robot::oi->GetOperatorJoystick())
{
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void RollersOut::Initialize()
{
	cougar::CougarDebug::startMethod("RollersOut::Initialize");
	cougar::CougarDebug::endMethod("RollersOut::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void RollersOut::Execute()
{
	Robot::intake->setRoller(1);
}

// Make this return true when this Command no longer needs to run execute()
bool RollersOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RollersOut::End()
{
	cougar::CougarDebug::startMethod("RollersOut::End");
	stopAll();
	cougar::CougarDebug::endMethod("RollersOut::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollersOut::Interrupted()
{
	cougar::CougarDebug::startMethod("RollersOut::Interrupted");
	End();
	cougar::CougarDebug::endMethod("RollersOut::Interrupted");
}

void RollersOut::stopAll() {
	Robot::intake->roller->StopMotor();
}
