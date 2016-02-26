#include "SetShooter.h"
#include "../../Robot.h"

SetShooter::SetShooter(float angle)
{
	cougar::CougarDebug::startMethod("SetShooter::SetShooter");
	Requires(Robot::shooter.get());
	this->angle_ = angle;
	cougar::CougarDebug::endMethod("SetShooter::SetShooter");
}

// Called just before this Command runs the first time
void SetShooter::Initialize()
{
	cougar::CougarDebug::startMethod("SetShooter::Initialize");
	cougar::CougarDebug::endMethod("SetShooter::Initialize");

}

// Called repeatedly when this Command is scheduled to run
void SetShooter::Execute()
{
	Robot::shooter->setAngleMotor(this->angle_ * TICKS_PER_DEGREE + ZERO_VALUE);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooter::IsFinished()
{
	return std::abs(Robot::shooter->angleMotor->GetSetpoint() - Robot::shooter->angleMotor->GetPosition()) < 10;
}

// Called once after isFinished returns true
void SetShooter::End()
{
	cougar::CougarDebug::startMethod("SetShooter::End");
	Robot::shooter->angleMotor->StopMotor();
	cougar::CougarDebug::endMethod("SetShooter::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooter::Interrupted()
{
	cougar::CougarDebug::startMethod("SetShooter::Interrupted");
	End();
	cougar::CougarDebug::endMethod("SetShooter::Interrupted");
}
