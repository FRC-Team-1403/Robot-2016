#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		Subsystem("Intake")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	//this->ultrasonic = RobotMap::intakeUltrasonic;
	this->angleAirCylinder = RobotMap::intakeAngleAirCylinder;
	this->liftAirCylinder = RobotMap::intakeLiftAirCylinder;
	this->compressor = RobotMap::compressor;
	compressor->SetClosedLoopControl(true);
	compressor->Start();
}

void Intake::InitDefaultCommand()
{
}

void Intake::setAngleAirCylinder(enum DoubleSolenoid::Value position) {
	angleAirCylinder->Set(position);
}

void Intake::setLiftAirCylinder(enum DoubleSolenoid::Value position) {
	liftAirCylinder->Set(position);
}

enum DoubleSolenoid::Value Intake::getAngleAirCylinderValue() {
	return angleAirCylinder->Get();
}

enum DoubleSolenoid::Value Intake::getLiftAirCylinderValue() {
	return liftAirCylinder->Get();
}

void Intake::setRoller(double value) {
	roller->Set(value);
}

bool Intake::getPressureSwitchValue() {
	return compressor->GetPressureSwitchValue();
}
