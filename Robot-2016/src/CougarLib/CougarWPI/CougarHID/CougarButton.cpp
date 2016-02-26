/*
 * CougarButton.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarWPI/CougarHID/CougarButton.h>

namespace cougar {

CougarButton::CougarButton(std::shared_ptr<CougarJoystick> stick, uint32_t buttonPort){
	CougarDebug::startMethod("CougarButton::CougarButton [port " + std::to_string(buttonPort) + "]");
	this->stick_ = stick;
	this->buttonPort = buttonPort;
	this->isDown_ = stick->GetRawButton(buttonPort);
	update();
	CougarDebug::endMethod("CougarButton::CougarButton [port " + std::to_string(buttonPort) + "]");
}

CougarButton::~CougarButton() {
	CougarDebug::startMethod("CougarButton::~CougarButton [port " + std::to_string(this->buttonPort) + "]");
	CougarDebug::startMethod("CougarButton::~CougarButton [port " + std::to_string(this->buttonPort) + "]");
}

bool CougarButton::getWasPressed() {
	update();
	return wasPressed_;
}

bool CougarButton::getWasReleased() {
	update();
	return wasReleased_;
}

bool CougarButton::Get() {
	update();
	return isDown_;
}

void CougarButton::update() {
	bool pressed = stick_->GetRawButton(buttonPort);
	wasPressed_ = pressed && !isDown_;
	wasReleased_ = !pressed && isDown_;
	isDown_ = pressed;
}

} /* namespace cougar */
