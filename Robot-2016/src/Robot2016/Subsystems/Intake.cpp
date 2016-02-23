#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		Subsystem("Intake")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	this->rollersAirCylinder = RobotMap::intakeAngleAirCylinder;
	this->triggerAirCylinder = RobotMap::intakeLiftAirCylinder;
	this->limitSwitch = RobotMap::intakeLimitSwitch;
	//this->compressor = RobotMap::compressor;
	//compressor->SetClosedLoopControl(true);
	//compressor->Start();
}

void Intake::InitDefaultCommand()
{
}

void Intake::liftRollersAirCylinder() {
	rollersAirCylinder->Set(DoubleSolenoid::kForward);
}

void Intake::dropRollersAirCylinder() {
	rollersAirCylinder->Set(DoubleSolenoid::kReverse);
}

void Intake::liftTriggerAirCylinder() {
	triggerAirCylinder->Set(DoubleSolenoid::kForward);
}

void Intake::dropTriggerAirCylinder() {
	triggerAirCylinder->Set(DoubleSolenoid::kReverse);
}

enum DoubleSolenoid::Value Intake::getRollersAirCylinderValue() {
	return rollersAirCylinder->Get();
}

enum DoubleSolenoid::Value Intake::getTriggerAirCylinderValue() {
	return triggerAirCylinder->Get();
}

void Intake::setRoller(double value) {
	roller->Set(value);
}

bool Intake::getPressureSwitchValue() {
	//return compressor->GetPressureSwitchValue();
	return false;
}

bool Intake::getLimitSwitchValue() {
	return limitSwitch->Get();
}
