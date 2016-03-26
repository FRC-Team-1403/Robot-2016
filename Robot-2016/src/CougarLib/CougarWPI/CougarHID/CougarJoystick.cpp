/*
 * CougarJoystick.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarJoystick.h"

namespace cougar {

int CougarJoystick::SMOOTHING_MODE;

CougarJoystick::CougarJoystick(uint32_t port, int smoothingMode, bool ignoreModsMinusSmoothing) {
	CougarDebug::startMethod((std::string("CougarJoystick::CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
	std::shared_ptr<Joystick> tmpJoystick(new Joystick(port));
	this->setSmoothingMode(smoothingMode);
	this->joystick_ = tmpJoystick;
	this->port_ = port;
	this->ignoreMods_ = ignoreModsMinusSmoothing;
	CougarDebug::endMethod((std::string("CougarJoystick::CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
}

CougarJoystick::~CougarJoystick() {
	CougarDebug::startMethod((std::string("CougarJoystick::~CougarJoystick [port ") + std::to_string(port_) + std::string("]")).c_str());
	CougarDebug::endMethod((std::string("CougarJoystick::~CougarJoystick [port ") + std::to_string(port_) + std::string("]")).c_str());
}

void CougarJoystick::setSmoothingMode(int32_t mode) {
	CougarDebug::startMethod("CougarJoystick::setSmoothingMode");
	SMOOTHING_MODE = mode;
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarJoystick smoothing mode set to %d", mode);
	CougarDebug::endMethod("CougarJoystick::setSmoothingMode");
}

bool CougarJoystick::GetButtonA() {
	return this->joystick_->GetRawButton(1);
}

bool CougarJoystick::GetButtonB() {
	return this->joystick_->GetRawButton(2);
}

bool CougarJoystick::GetButtonX() {
	return this->joystick_->GetRawButton(3);
}

bool CougarJoystick::GetButtonY() {
	return this->joystick_->GetRawButton(4);
}

bool CougarJoystick::GetButtonRB() {
	return this->joystick_->GetRawButton(6);
}

bool CougarJoystick::GetButtonLB() {
	return this->joystick_->GetRawButton(5);
}

bool CougarJoystick::GetButtonRT() {
	return this->joystick_->GetRawAxis(3) > 0.5;
}

bool CougarJoystick::GetButtonLT() {
	return this->joystick_->GetRawAxis(2) > 0.5;
}

bool CougarJoystick::GetButtonStart() {
	return this->joystick_->GetRawButton(8);
}

bool CougarJoystick::GetButtonBack() {
	return this->joystick_->GetRawButton(7);
}

bool CougarJoystick::GetRawButton(uint32_t port) {
	return this->joystick_->GetRawButton(port);
}

bool CougarJoystick::GetButtonLeftStick() {
	return this->GetRawButton(9);
}

bool CougarJoystick::GetButtonRightStick() {
	return this->GetRawButton(10);
}

bool CougarJoystick::GetButtonBothSticks() {
	return this->GetButtonRightStick() && this->GetButtonLeftStick();
}

bool CougarJoystick::IsZeroAxis(uint32_t axis) {
	return std::abs(this->GetRawAxis(axis)) <= 0.075;
}

bool CougarJoystick::AreZeroSticks() {
	return  this->IsZeroAxis(0) &&
			this->IsZeroAxis(1) &&
			this->IsZeroAxis(4) &&
			this->IsZeroAxis(5);
}

float CougarJoystick::GetStickLeftAxisX() {
	return this->getAxis(0);
}

float CougarJoystick::GetStickLeftAxisY() {
	return this->getAxis(1);
}

float CougarJoystick::GetStickRightAxisX() {
	return this->getAxis(4);
}

float CougarJoystick::GetStickRightAxisY() {
	return this->getAxis(5);
}

float CougarJoystick::GetRawAxis(uint32_t axis) {
	return this->joystick_->GetRawAxis(axis);
}

float CougarJoystick::getAxis(uint32_t axis) {
	float val = Smoothing::get(this->GetRawAxis(axis));

	/*
	 * Handles small deadzone issues with the joysticks
	 * that get amplified by the smoothing algorithm.
	 */
	if (this->IsZeroAxis(axis)) { return 0; }

	if (this->ignoreMods_) { return val; }

	if (this->GetButtonLT()) { val *= SCALING_FACTOR; }
	if (this->GetButtonRT()) { val *= -1; }
	return val;
}

} /* namespace cougar */
