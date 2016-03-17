#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		cougar::CougarSubsystem("Intake")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	this->rollersAirCylinder = RobotMap::intakeAngleAirCylinder;
	this->triggerAirCylinder = RobotMap::intakeLiftAirCylinder;
	this->ballSwitch = RobotMap::intakeBallSwitch;
}

void Intake::InitDefaultCommand()
{
}

void Intake::stop() {
	this->roller->StopMotor();
}

void Intake::liftRollersAirCylinder() {
	rollersAirCylinder->Set(cougar::CougarDoubleSolenoid::kReverse);
}

void Intake::dropRollersAirCylinder() {
	rollersAirCylinder->Set(cougar::CougarDoubleSolenoid::kForward);
}

void Intake::liftTriggerAirCylinder() {
	triggerAirCylinder->Set(false);
}

void Intake::dropTriggerAirCylinder() {
	triggerAirCylinder->Set(true);
}

enum cougar::CougarDoubleSolenoid::Value Intake::getRollersAirCylinderValue() {
	return rollersAirCylinder->Get();
}

bool Intake::getTriggerAirCylinderValue() {
	return triggerAirCylinder->Get();
}

void Intake::setRoller(double value) {
	roller->Set(value);
}

bool Intake::getBallSwitchValue() {
	return ballSwitch->Get();
}
