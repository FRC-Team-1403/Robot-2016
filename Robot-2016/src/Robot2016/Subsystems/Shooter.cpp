#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/AimWithJoystick.h"

Shooter::Shooter() :
		Subsystem("Shooter")
{
	bottomRoller = RobotMap::shooterRollerBottom;
	topRoller = RobotMap::shooterRollerTop;
	angleMotor = RobotMap::shooterAngleMotor;
	cameraServo = RobotMap::shooterCameraServo;
	//table = NetworkTable::GetTable("SmartDashboard");
	i = 0;
}

void Shooter::InitDefaultCommand()
{
	SetDefaultCommand(new AimWithJoystick());
}

void Shooter::stop() {
	this->angleMotor->StopMotor();
	this->topRoller->StopMotor();
	this->bottomRoller->StopMotor();
}
double getAngle(){
	//return table->GetNumber("azimuth", 0);
	return 0;
}
double getDistance(){
	//return table->GetNumber("distance",0);
	return 0;
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

void Shooter::setAngleMotor(double position) {
	cougar::CougarDebug::debugPrinter("Shooter setanglemotor " + std::to_string(position));
	angleMotor->Set(position);
}

void Shooter::setCameraServo(double position) {
	this->cameraServo->Set(position);
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

float Shooter::potToAngle(float pot) {
	return (pot - cougar::CougarConstants::SHOOTER_DECK_ANGLE_ZERO) / cougar::CougarConstants::SHOOTER_DECK_TICKS_PER_DEGREE;
}

float Shooter::angleToPot(float angle) {
	return angle * cougar::CougarConstants::SHOOTER_DECK_TICKS_PER_DEGREE + cougar::CougarConstants::SHOOTER_DECK_ANGLE_ZERO;
}

/*
int Shooter::getI() {
	return i;
}

void Shooter::setI(int value) {
	i = value;
}
*/
