#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		Subsystem("Intake")
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
	this->roller->Set(0);
}

void Intake::liftRollersAirCylinder() {
	rollersAirCylinder->Set(DoubleSolenoid::kReverse);
}

void Intake::dropRollersAirCylinder() {
	rollersAirCylinder->Set(DoubleSolenoid::kForward);
}

void Intake::liftTriggerAirCylinder() {
	triggerAirCylinder->Set(false);
}

void Intake::dropTriggerAirCylinder() {
	triggerAirCylinder->Set(true);
}

enum DoubleSolenoid::Value Intake::getRollersAirCylinderValue() {
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
