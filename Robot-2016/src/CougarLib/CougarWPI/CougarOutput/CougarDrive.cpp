/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

// TODO Finish debugging for this class.
// Not doing it right now because TrajectoryLib needs to be fixed first.

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right, std::string name) {
//	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(left, right));
	this->drive_ = tmpDrive;
	this->name_ = name;
//	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::~CougarDrive() {
//	CougarDebug::startMethod("CougarDrive::~CougarDrive " + this->GetName());
//	CougarDebug::endMethod("CougarDrive::~CougarDrive " + this->GetName());
}

void CougarDrive::Drive(float outputMagnitude, float curve) const{
	this->drive_->Drive(outputMagnitude, curve);
}

void CougarDrive::TankDrive(std::shared_ptr<CougarJoystick> joystick, bool reversed,  bool squaredInputs /* = true */) {
	int reverse = reversed ? -1 : 1;
	this->drive_->TankDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickRightAxisY() * this->speedFactor(joystick) * reverse, squaredInputs);
}
void CougarDrive::ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick /* LEFT or RIGHT */ , bool reversed, bool squaredInputs /* = true */) {
	int reverse = reversed ? -1 : 1;
	if (stick == LEFT) {
		this->drive_->ArcadeDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickLeftAxisX() * this->speedFactor(joystick) * reverse, squaredInputs);
	} else if (stick == RIGHT) {
		this->drive_->ArcadeDrive(joystick->GetStickRightAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickRightAxisX() * this->speedFactor(joystick) * reverse, squaredInputs);
	} else {
		CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
	}
}

void CougarDrive::SetSensitivity(float sensitivity) {
	this->drive_->SetSensitivity(sensitivity);
}

void CougarDrive::SetMaxOutput(double maxOutput) {
	this->drive_->SetMaxOutput(maxOutput);
}

void CougarDrive::SetExpiration(float timeout) {
	this->drive_->SetExpiration(timeout);
}

float CougarDrive::GetExpiration() const {
	return this->drive_->GetExpiration();
}

bool CougarDrive::IsAlive() const {
	return this->drive_->IsAlive();
}

void CougarDrive::StopMotor() {
	this->drive_->StopMotor();
}

bool CougarDrive::IsSafetyEnabled() const {
	return this->drive_->IsSafetyEnabled();
}

void CougarDrive::SetSafetyEnabled(bool enabled) {
	this->drive_->SetSafetyEnabled(enabled);
}
std::string CougarDrive::GetName() const {
	return this->name_;
}

const char *CougarDrive::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<RobotDrive> CougarDrive::CougarDriveExtractor::ExtractDrive(std::shared_ptr<CougarDrive> drive) {
	return drive->GetDrive();
}

std::shared_ptr<RobotDrive> CougarDrive::CougarDriveExtractor::ExtractDrive(const CougarDrive &drive) {
	std::shared_ptr<CougarDrive> tmp(&(CougarDrive&)drive);
	return ExtractDrive(tmp);
}

std::shared_ptr<RobotDrive> CougarDrive::GetDrive() {
	return this->drive_;
}


float CougarDrive::speedFactor(std::shared_ptr<CougarJoystick> joystick) {
	const float SPEED_FACTOR = 0.5;
	return joystick->GetButtonY() ? SPEED_FACTOR : 1;
}

} /* namespace cougar */
