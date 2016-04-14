#include "AimWithJoystick.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"

#include "../../Robot.h"

AimWithJoystick::AimWithJoystick(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("AimWithJoystick", joy, true)
{
	cougar::CougarDebug::startMethod("AimWithJoystick::AimWithJoystick");
	Requires(Robot::shooter.get());
	cam = 0.750;
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
	if (Robot::oi->GetOperatorJoystick()->GetButtonRT()) {
		Robot::shooter->angleMotor->Set(Robot::oi->GetOperatorJoystick()->GetStickRightAxisY());
		Robot::shooter->setTopRoller(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY() * -1);
		Robot::shooter->setBottomRoller(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY() * -1);
		//cam = Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY();
		//Robot::shooter->setCameraServo(Robot::oi->GetOperatorJoystick()->GetStickLeftAxisY());
	} else {
		Robot::shooter->cameraServo->Set(Robot::oi->GetOperatorJoystick()->GetStickRightAxisY());
		//Robot::shooter->setCameraServo(cam);
	}
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
	//Robot::shooter->angleMotor->SetControlMode(CANSpeedController::kPosition);
	stopAll();
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

void AimWithJoystick::stopAll() {
	//Robot::shooter->angleMotor->SetControlMode(CANSpeedController::kPosition);
	//Robot::shooter->topRoller->SetControlMode(CANSpeedController::kSpeed);
	//Robot::shooter->bottomRoller->SetControlMode(CANSpeedController::kSpeed);
}
