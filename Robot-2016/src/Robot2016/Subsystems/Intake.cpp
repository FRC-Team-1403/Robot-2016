#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		cougar::CougarSubsystem("Intake")
{
	this->roller = RobotMap::intakeRoller;
	this->addObject(roller);
	this->ballSwitch = RobotMap::intakeBallSwitch;
	this->addObject(this->ballSwitch);
	this->rollersAirCylinder = RobotMap::intakeAngleAirCylinder;
	this->addObject(rollersAirCylinder);
	this->triggerAirCylinder = RobotMap::intakeLiftAirCylinder;
	this->addObject(triggerAirCylinder);
	this->ballSwitch = RobotMap::intakeBallSwitch;
}

void Intake::InitDefaultCommand()
{
}

void Intake::stop() {
	this->roller->StopMotor();
}

void Intake::liftRollersAirCylinder() {
	rollersAirCylinder->DoubleSolenoid::Set(cougar::CougarDoubleSolenoid::kReverse);
}

void Intake::dropRollersAirCylinder() {
	rollersAirCylinder->DoubleSolenoid::Set(cougar::CougarDoubleSolenoid::kForward);
}

void Intake::liftTriggerAirCylinder() {
	triggerAirCylinder->Solenoid::Set(false);
}

void Intake::dropTriggerAirCylinder() {
	triggerAirCylinder->Solenoid::Set(true);
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
