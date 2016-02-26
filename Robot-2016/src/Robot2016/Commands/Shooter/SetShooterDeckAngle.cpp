#include "SetShooterDeckAngle.h"
#include "../../Robot.h"

SetShooterDeckAngle::SetShooterDeckAngle(float angle)
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::SetShooterDeckAngle");
	Requires(Robot::shooter.get());
	this->angle_ = angle;
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::SetShooterDeckAngle");
}

// Called just before this Command runs the first time
void SetShooterDeckAngle::Initialize()
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::Initialize");
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::Initialize");

}

// Called repeatedly when this Command is scheduled to run
void SetShooterDeckAngle::Execute()
{
	Robot::shooter->setAngleMotor(this->angle_ * TICKS_PER_DEGREE + ZERO_VALUE);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterDeckAngle::IsFinished()
{
	return std::abs(Robot::shooter->angleMotor->GetSetpoint() - Robot::shooter->angleMotor->GetPosition()) < 10;
}

// Called once after isFinished returns true
void SetShooterDeckAngle::End()
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::End");
	Robot::shooter->angleMotor->StopMotor();
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterDeckAngle::Interrupted()
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::Interrupted");
	End();
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::Interrupted");
}
