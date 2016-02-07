/*
 * CougarJoystick.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarJoystick.h"

namespace cougar {

CougarJoystick::CougarJoystick(uint32_t port) {
	std::shared_ptr<Joystick> tmpJoystick(new Joystick(port));
	this->joystick_ = tmpJoystick;
	this->LX = new Accel(0);
	this->LY = new Accel(1);
	this->RX = new Accel(4);
	this->RY = new Accel(5);
}

CougarJoystick::~CougarJoystick() {
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

float CougarJoystick::GetStickLeftAxisX() {
	if (!SMOOTHING) {
		return this->joystick_->GetRawAxis(0);
	} else {

	}
}

float CougarJoystick::GetStickLeftAxisY() {
	if (!SMOOTHING) {
		return this->joystick_->GetRawAxis(1);
	}
	else {
		float val = this->LX->getVel(this->joystick_->GetRawAxis(1));
		CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "Motor set to %f", val);
		return val;

	}
}

float CougarJoystick::GetStickRightAxisX() {
	if (!SMOOTHING) {
		return this->joystick_->GetRawAxis(4);
	} else {

	}
}

float CougarJoystick::GetStickRightAxisY() {
	if (!SMOOTHING) {
		return this->joystick_->GetRawAxis(5);
	} else {

	}
}

float CougarJoystick::GetRawAxis(uint32_t axis) {
	return this->joystick_->GetRawAxis(axis);
}

} /* namespace cougar */
