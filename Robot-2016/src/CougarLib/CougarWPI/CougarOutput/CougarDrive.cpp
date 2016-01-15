/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right, std::string name) {
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(left, right));
	this->drive_ = tmpDrive;
	this->name_ = name;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarDrive %s constructed", this->GetCName());
}

CougarDrive::~CougarDrive() {
}

void CougarDrive::Drive(float outputMagnitude, float curve) const{
	this->drive_->Drive(outputMagnitude, curve);
}

void CougarDrive::TankDrive(std::shared_ptr<CougarJoystick> joystick, bool squaredInputs /* = true */) {
	if (SMOOTHING) {
		// TODO: Implement input smoothing
	} else {
		this->drive_->TankDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick), joystick->GetStickRightAxisY() * this->speedFactor(joystick), squaredInputs);
	}
}
void CougarDrive::ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs /* = true */) {
	if (SMOOTHING) {
		// TODO: Implement input smoothing
	} else {
		if (stick == LEFT) {
			this->drive_->ArcadeDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick), joystick->GetStickLeftAxisX() * this->speedFactor(joystick), squaredInputs);
		} else if (stick == RIGHT) {
			this->drive_->ArcadeDrive(joystick->GetStickRightAxisY() * this->speedFactor(joystick), joystick->GetStickRightAxisX() * this->speedFactor(joystick), squaredInputs);
		} else {
			CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
		}
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
	return drive.GetDrive();
}

std::shared_ptr<RobotDrive> CougarDrive::GetDrive() {
	return this->drive_;
}

const bool CougarDrive::GetSmoothing() {
	return SMOOTHING;
}

float CougarDrive::speedFactor(std::shared_ptr<CougarJoystick> joystick) {
	const float SPEED_FACTOR = 0.5;
	return joystick->GetButtonY() ? SPEED_FACTOR : 1;
}

} /* namespace cougar */
