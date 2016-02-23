#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/AimWithJoystick.h"

Shooter::Shooter() :
		Subsystem("Shooter")
{
	bottomRoller = RobotMap::shooterRollerBottom;
	topRoller = RobotMap::shooterRollerTop;
	angleMotor = RobotMap::shooterAngleMotor;
}

void Shooter::InitDefaultCommand()
{
	SetDefaultCommand(new AimWithJoystick());
}

double Shooter::getPotentiometer() {
	return angleMotor->GetEncPosition();
}

void Shooter::setTopRoller(double velocity) {
	this->topRoller->Set(velocity);
}
void Shooter::setBottomRoller(double velocity) {
	this->bottomRoller->Set(velocity);
}

void Shooter::setAngleMotor(double velocity) {
	angleMotor->Set(velocity);
}
int Shooter::getAngleMotorDistance() {
	return this->angleMotor->GetAnalogIn();
}

int Shooter::getAngleMotorVelocity() {
	return this->angleMotor->GetAnalogInVel();
}

int Shooter::getTopRollerDistance() {
	return this->topRoller->GetEncPosition();
}

int Shooter::getBottomRollerDistance() {
	return this->bottomRoller->GetEncPosition();
}

int Shooter::getTopRollerVelocity() {
	return this->topRoller->GetEncVel();
}

int Shooter::getBottomRollerVelocity() {
	return this->bottomRoller->GetEncVel();
}
