/*
 * CougarJoystick.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarJoystick.h"

namespace cougar {

CougarJoystick::CougarJoystick(uint32_t port) {
	CougarDebug::startMethod((std::string("CougarJoystick::CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
	std::shared_ptr<Joystick> tmpJoystick(new Joystick(port));
	this->joystick_ = tmpJoystick;
	this->port = port;
	CougarDebug::endMethod((std::string("CougarJoystick::CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
}

CougarJoystick::~CougarJoystick() {
	CougarDebug::startMethod((std::string("CougarJoystick::~CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
	CougarDebug::endMethod((std::string("CougarJoystick::~CougarJoystick [port ") + std::to_string(port) + std::string("]")).c_str());
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

float CougarJoystick::GetStickLeftAxisX() {
	if (!GetButtonX()) {
		return this->joystick_->GetRawAxis(0);
	} else {
		return Smoothing::get(this->joystick_->GetRawAxis(0));
	}
}

float CougarJoystick::GetStickLeftAxisY() {
	if (!GetButtonX()) {
		return this->joystick_->GetRawAxis(1);
	}
	else {
		return Smoothing::get(this->joystick_->GetRawAxis(1));
	}
}

float CougarJoystick::GetStickRightAxisX() {
	if (!GetButtonX()) {
		return this->joystick_->GetRawAxis(4);
	} else {
		return Smoothing::get(this->joystick_->GetRawAxis(4));
	}
}

float CougarJoystick::GetStickRightAxisY() {
	if (!GetButtonX()) {
		return this->joystick_->GetRawAxis(5);
	} else {
		return Smoothing::get(this->joystick_->GetRawAxis(5));
	}
}

float CougarJoystick::GetRawAxis(uint32_t axis) {
	return this->joystick_->GetRawAxis(axis);
}

} /* namespace cougar */
