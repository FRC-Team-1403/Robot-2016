#include "CougarWait.h"

CougarWait::CougarWait(float time)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	this->init_time_ = 0;
	this->time_ = time;
}

// Called just before this Command runs the first time
void CougarWait::Initialize()
{
	this->init_time_ = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void CougarWait::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool CougarWait::IsFinished()
{
	return Timer::GetFPGATimestamp() - init_time_ >= time_;
}

// Called once after isFinished returns true
void CougarWait::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CougarWait::Interrupted()
{

}
