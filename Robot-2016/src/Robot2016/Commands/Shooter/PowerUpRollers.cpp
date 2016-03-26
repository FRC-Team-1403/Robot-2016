#include "PowerUpRollers.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


PowerUpRollers::PowerUpRollers(float topRollerPower, float bottomRollerPower, float time) :
	cougar::CougarCommand("PowerUpRollers", Robot::oi->GetOperatorJoystick())
{
	cougar::CougarDebug::startMethod("PowerUpRollers::PowerUpRollers");
	Requires(Robot::shooter.get());
	this->topRollerPower_ = topRollerPower;
	this->bottomRollerPower_ = bottomRollerPower;
	this->init_time_ = 0;
	this->time_ = time;
	cougar::CougarDebug::endMethod("PowerUpRollers::PowerUpRollers");
}

// Called just before this Command runs the first time
void PowerUpRollers::Initialize()
{
	cougar::CougarDebug::startMethod("PowerUpRollers::Initialize");
	this->init_time_ = Timer::GetFPGATimestamp();

	cougar::CougarDebug::endMethod("PowerUpRollers::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void PowerUpRollers::Execute()
{
	Robot::shooter->setTopRoller(this->topRollerPower_ * cougar::CougarConstants::SHOOTER_ROLLER_MAX_SPEED);
	Robot::shooter->setBottomRoller(this->bottomRollerPower_ * cougar::CougarConstants::SHOOTER_ROLLER_MAX_SPEED);
}

// Make this return true when this Command no longer needs to run execute()
bool PowerUpRollers::IsFinished()
{
	std::cout << "Setpoint top: " << Robot::shooter->topRoller->GetSetpoint() << "\n";
	std::cout << "Setpoint bottom: " << Robot::shooter->bottomRoller->GetSetpoint() << "\n";
	std::cout << "Speed top: " << Robot::shooter->topRoller->GetSpeed() << "\n";
	std::cout << "Speed bottom: " << Robot::shooter->bottomRoller->GetSpeed() << "\n";


	return std::abs(Robot::shooter->topRoller->GetSetpoint() - Robot::shooter->topRoller->GetSpeed()) < 10 &&
		   std::abs(Robot::shooter->bottomRoller->GetSetpoint() - Robot::shooter->bottomRoller->GetSpeed()) < 10 &&
		   Timer::GetFPGATimestamp() - init_time_ >= time_;
}

// Called once after isFinished returns true
void PowerUpRollers::End()
{
	cougar::CougarDebug::startMethod("PowerUpRollers::End");
	stopAll();
	cougar::CougarDebug::endMethod("PowerUpRollers::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PowerUpRollers::Interrupted()
{
	cougar::CougarDebug::startMethod("PowerUpRollers::Interrupted");
	End();
	cougar::CougarDebug::endMethod("PowerUpRollers::Interrupted");
}

void PowerUpRollers::stopAll() {
	Robot::intake->liftTriggerAirCylinder();	// lol hax
	Robot::shooter->topRoller->StopMotor();
	Robot::shooter->bottomRoller->StopMotor();
}
