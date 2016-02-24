#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Commands/DriveTrain/DriveWithJoystick.h"

DriveTrain::DriveTrain() :
		Subsystem("DriveTrain")
{
	this->driveT = RobotMap::drive;
	this->driveTrainLeftEncoder = RobotMap::driveTrainLeftEncoder;
	this->driveTrainRightEncoder = RobotMap::driveTrainRightEncoder;
	this->driveTrainGyro = RobotMap::driveTrainGyro;
	this->time = Timer::GetFPGATimestamp();
	this->angle = this->getGyroAngleInRadians();
	this->distance = getDistance();
	this->vel = 0;
	this->acc = 0;
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::drive() {
	if (Robot::oi->GetDriverJoystick()->GetButtonStart()) {
		this->driveT->Drive(Robot::oi->GetDriverJoystick()->GetStickLeftAxisY() * -1, 0);
	}
	this->driveT->TankDrive(Robot::oi->GetDriverJoystick(), true, false);
}

double DriveTrain::getDistance() {
	return (this->getLeftEncoderDistance() + this->getRightEncoderDistance()) / 2.0;
}
double DriveTrain::getVelocity() {
	return (this->driveTrainLeftEncoder->GetRate() * -1 + this->driveTrainRightEncoder->GetRate()) / 2.0;
}
double DriveTrain::getAcceleration() {
	double v = this->getVelocity();
	double t = Timer::GetFPGATimestamp();
	double result = (v - vel) / (t - time);
	this->time = t;
	this->vel = v;

	return result;
}

double DriveTrain::getJerk() {
	double a = this->getAcceleration();
	double t = Timer::GetFPGATimestamp();
	double result = (a - acc) / (t - time);
	this->acc = a;
	this->time = t;

	return result;
}

double DriveTrain::getAngularVelocity() {
	return (this->driveTrainGyro->GetRate() * M_PI) / 180.0;
}

void DriveTrain::setLeftRightPower(double leftPower, double rightPower) {
	this->driveT->TankDrive(leftPower, rightPower);
}

void DriveTrain::stop() {
	setLeftRightPower(0, 0);
}

 double DriveTrain::getRightEncoderDistance() {
	return driveTrainRightEncoder->GetDistance();
}

 double DriveTrain::getLeftEncoderDistance() {
	return driveTrainLeftEncoder->GetDistance();
}

 double DriveTrain::getGyroAngleInRadians() {
	 return (driveTrainGyro->GetAngle() *M_PI) / 180.0;
}

 void DriveTrain::resetGyro() {
	 driveTrainGyro->Reset();
}

 void DriveTrain::resetEncoders() {
	 this->driveTrainLeftEncoder->Reset();
	 this->driveTrainRightEncoder->Reset();
}
