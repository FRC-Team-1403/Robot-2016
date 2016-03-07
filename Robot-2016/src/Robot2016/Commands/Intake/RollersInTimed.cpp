#include "RollersInTimed.h"
#include "../../Robot.h"

RollersInTimed::RollersInTimed(float time)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
	this->start_time_ = -1;
	this->time_ = time;
}

// Called just before this Command runs the first time
void RollersInTimed::Initialize()
{
	this->start_time_ = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void RollersInTimed::Execute()
{
	Robot::intake->setRoller(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool RollersInTimed::IsFinished()
{
	return (this->start_time_ > 0 && Timer::GetFPGATimestamp() - start_time_ >= time_) || !Robot::intake->getBallSwitchValue();
}

// Called once after isFinished returns true
void RollersInTimed::End()
{
	Robot::intake->setRoller(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollersInTimed::Interrupted()
{
	End();
}
