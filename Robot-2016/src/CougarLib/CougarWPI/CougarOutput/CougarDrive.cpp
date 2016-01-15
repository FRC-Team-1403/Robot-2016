/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right) {
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(left, right));
	this->drive_ = tmpDrive;
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
			throw "An invalid analog stick has been specified...";
		}
	}
}

void CougarDrive::SetSensitivity(float sensitivity) const {
	this->drive_->SetSensitivity(sensitivity);
}

void CougarDrive::SetMaxOutput(double maxOutput) const {
	this->drive_->SetMaxOutput(maxOutput);
}

void CougarDrive::SetExpiration(float timeout) const {
	this->drive_->SetExpiration(timeout);
}

float CougarDrive::GetExpiration() const {
	return this->drive_->GetExpiration();
}

bool CougarDrive::IsAlive() const {
	return this->drive_->IsAlive();
}

void CougarDrive::StopMotor() const {
	this->drive_->StopMotor();
}

bool CougarDrive::IsSafetyEnabled() const {
	return this->drive_->IsSafetyEnabled();
}

void CougarDrive::SetSafetyEnabled(bool enabled) const {
	this->drive_->SetSafetyEnabled(enabled);
}

float CougarDrive::speedFactor(std::shared_ptr<CougarJoystick> joystick) {
	const float SPEED_FACTOR = 0.5;
	return joystick->GetButtonY() ? SPEED_FACTOR : 1;
}

} /* namespace cougar */
