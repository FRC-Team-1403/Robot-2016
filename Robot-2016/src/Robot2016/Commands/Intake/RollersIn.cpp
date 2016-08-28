#include "RollersIn.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"

RollersIn::RollersIn(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("RollersIn", joy)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void RollersIn::Initialize()
{
	cougar::CougarDebug::startMethod("RollersIn::Initialize");
	cougar::CougarDebug::endMethod("RollersIn::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void RollersIn::Execute()
{
	Robot::intake->setRoller(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool RollersIn::IsFinished()
{
	return !Robot::intake->getBallSwitchValue();
}

// Called once after isFinished returns true
void RollersIn::End()
{
	cougar::CougarDebug::startMethod("RollersIn::End");
	stopAll();
	cougar::CougarDebug::endMethod("RollersIn::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollersIn::Interrupted()
{
	cougar::CougarDebug::startMethod("RollersIn::Interrupted");
	End();
	cougar::CougarDebug::endMethod("RollersIn::Interrupted");
}

void RollersIn::stopAll() {
	Robot::intake->roller->StopMotor();
}
