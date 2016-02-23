#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/AimWithJoystick.h"

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
