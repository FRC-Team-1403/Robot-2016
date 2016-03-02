#include "AimWithJoystick.h"
#include "../../Robot.h"

AimWithJoystick::AimWithJoystick()
{
	cougar::CougarDebug::startMethod("AimWithJoystick::AimWithJoystick");
	Requires(Robot::shooter.get());
	cougar::CougarDebug::endMethod("AimWithJoystick::AimWithJoystick");
}

// Called just before this Command runs the first time
void AimWithJoystick::Initialize()
{
	cougar::CougarDebug::startMethod("AimWithJoystick::Initialize");
	Robot::shooter->angleMotor->SetControlMode(CANSpeedController::kPercentVbus);
	Robot::shooter->topRoller->SetControlMode(CANSpeedController::kPercentVbus);
	Robot::shooter->bottomRoller->SetControlMode(CANSpeedController::kPercentVbus);
	cougar::CougarDebug::endMethod("AimWithJoystick::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void AimWithJoystick::Execute()
{
	//if (Robot::oi->GetOperatorJoystick()->GetButtonBack()) {
	//	Robot::shooter->setCameraServo(.5 * Robot::oi->GetOperatorJoystick()->GetStickRightAxisY() + 0.5);
	//} else {
		Robot::shooter->angleMotor->Set(Robot::oi->GetOperatorJoystick()->GetStickRightAxisY());
		std::cout << "Set: " << Robot::oi->GetOperatorJoystick()->GetStickRightAxisY() << "\n";
		std::cout << "Actual: " << Robot::shooter->angleMotor->Get() << "\n";
		Robot::shooter->setCameraServo(1);
	//}

	Robot::shooter->setTopRoller(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY() * -1);
	Robot::shooter->setBottomRoller(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY() * -1);

}

// Make this return true when this Command no longer needs to run execute()
bool AimWithJoystick::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AimWithJoystick::End()
{
	cougar::CougarDebug::startMethod("AimWithJoystick::End");
	cougar::CougarDebug::endMethod("AimWithJoystick::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimWithJoystick::Interrupted()
{
	cougar::CougarDebug::startMethod("AimWithJoystick::Interrupted");
	End();
	cougar::CougarDebug::endMethod("AimWithJoystick::Interrupted");
}
