/*
 * CougarJoystick.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarJoystick.h"

namespace cougar {

CougarJoystick::CougarJoystick(uint32_t port) {
	this->joystick_ = new Joystick(port);

}

CougarJoystick::~CougarJoystick() {
	delete this->joystick_;
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

bool CougarJoystick::GetButtonRT() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonLT() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonRB() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonLB() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonDPADUp() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonDPADDown() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonDPADLeft() {
	// TODO
	return false;
}

bool CougarJoystick::GetButtonDPADRight() {
	// TODO
	return false;
}

double CougarJoystick::GetStickLeftAxisX() {
	// TODO
	return false;
}

double CougarJoystick::GetStickLeftAxisY() {
	// TODO
	return false;
}

double CougarJoystick::GetStickRightAxisX() {
	// TODO
	return false;
}

double CougarJoystick::GetStickRightAxisY() {
	// TODO
	return false;
}

} /* namespace cougar */
