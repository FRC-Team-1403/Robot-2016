#include "Drive.h"
#include "../../Robot.h"

Drive::Drive(float left, float right, float time)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::driveTrain.get());
	this->init_time_ = 0;
	this->time_ = time;
	this->left_ = left;
	this->right_ = right;
}

// Called just before this Command runs the first time
void Drive::Initialize()
{
	this->init_time_ = Timer::GetFPGATimestamp();

}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute()
{
	Robot::driveTrain->setLeftRightPower(left_, right_);
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished()
{
	return Timer::GetFPGATimestamp() - init_time_ >= time_;
}

// Called once after isFinished returns true
void Drive::End()
{
	Robot::driveTrain->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted()
{
	End();
}
