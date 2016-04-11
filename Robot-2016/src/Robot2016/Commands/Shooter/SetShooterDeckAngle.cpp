#include "SetShooterDeckAngle.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


SetShooterDeckAngle::SetShooterDeckAngle(float angle, std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("SetShooterDeckAngle", joy)
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::SetShooterDeckAngle");
	Requires(Robot::shooter.get());
	this->angle_ = Robot::shooter->angleToPot(angle);
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::SetShooterDeckAngle");
}

// Called just before this Command runs the first time
void SetShooterDeckAngle::Initialize()
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::Initialize");
	Robot::shooter->angleMotor->SetControlMode(CANSpeedController::kPosition);
	cougar::CougarDebug::endMethod("SetShooterDeckAngle::Initialize");

}

// Called repeatedly when this Command is scheduled to run
void SetShooterDeckAngle::Execute()
{
	if (!BANG_BANG) {

		std::cout << "Angle: " << this->angle_ << "\n";
		std::cout << "Angle val: " << this->angle_;// * cougar::CougarConstants::SHOOTER_DECK_TICKS_PER_DEGREE + cougar::CougarConstants::SHOOTER_DECK_ANGLE_ZERO << "\n";
		std::cout << "Actual Setpoint: " << Robot::shooter->angleMotor->GetSetpoint();
		std::cout << "Actual Value: " << Robot::shooter->angleMotor->GetPosition();
		std::cout << "Error: " << Robot::shooter->angleMotor->GetClosedLoopError();
		Robot::shooter->setAngleMotor(this->angle_);// * cougar::CougarConstants::SHOOTER_DECK_TICKS_PER_DEGREE + cougar::CougarConstants::SHOOTER_DECK_ANGLE_ZERO);
	} else {
		if (Robot::shooter->getAngleMotorDistance() > this->angle_) {
			if (std::abs(Robot::shooter->getAngleMotorDistance() - this->angle_) > 55) {
				Robot::shooter->angleMotor->Set(0.75);
			}
			else if (std::abs(Robot::shooter->getAngleMotorDistance() - this->angle_) > 35){
				Robot::shooter->angleMotor->Set(0.45);
			} else {
				Robot::shooter->angleMotor->Set(0.3);
			}
		} else if (Robot::shooter->getAngleMotorDistance() < this->angle_) {
			if (std::abs(Robot::shooter->getAngleMotorDistance() - this->angle_) > 55) {
				Robot::shooter->angleMotor->Set(-1);
			}
			else if (std::abs(Robot::shooter->getAngleMotorDistance() - this->angle_) > 35){
				Robot::shooter->angleMotor->Set(-0.45);
			} else {
				Robot::shooter->angleMotor->Set(-0.3);
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterDeckAngle::IsFinished()
{

	//std::cout << "Setpoint: " << Robot::shooter->angleMotor->GetSetpoint() << "\n";
	//std::cout << "Position: " << Robot::shooter->angleMotor->GetPosition() << "\n";
	//std::cout << "analog  val" << Robot::shooter->getAngleMotorDistance() << "\n";
	//std::cout << "Speed: " << Robot::shooter->angleMotor->GetAnalogInVel() << "\n";

	if (!BANG_BANG)
		return std::abs(Robot::shooter->angleMotor->GetSetpoint() - Robot::shooter->angleMotor->GetPosition()) < 0.001;
	else
		return std::abs(Robot::shooter->getAngleMotorDistance() - this->angle_) < 2.7;
}

// Called once after isFinished returns true
void SetShooterDeckAngle::End()
{
	cougar::CougarDebug::startMethod("SetShooterDeckAngle::End");
	Robot::shooter->angleMotor->SetControlMode(CANSpeedController::kPercentVbus);
	stopAll();
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

void SetShooterDeckAngle::stopAll() {
	Robot::shooter->angleMotor->StopMotor();
}
