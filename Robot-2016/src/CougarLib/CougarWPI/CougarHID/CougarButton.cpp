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
	this->stick = stick;
	this->buttonPort = buttonPort;
	this->isDown = stick->GetRawButton(buttonPort);
	update();
	CougarDebug::endMethod("CougarButton::CougarButton [port " + std::to_string(buttonPort) + "]");
}

CougarButton::~CougarButton() {
	CougarDebug::startMethod("CougarButton::~CougarButton [port " + std::to_string(this->buttonPort) + "]");
	CougarDebug::startMethod("CougarButton::~CougarButton [port " + std::to_string(this->buttonPort) + "]");
}

bool CougarButton::getWasPressed() {
	update();
	return wasPressed;
}

bool CougarButton::getWasReleased() {
	update();
	return wasReleased;
}

bool CougarButton::get() {
	update();
	return isDown;
}

void CougarButton::update() {
	CougarDebug::startMethod("CougarButton::update");
	bool pressed = stick->GetRawButton(buttonPort);
	wasPressed = pressed && !isDown;
	wasReleased = !pressed && isDown;
	isDown = pressed;
	CougarDebug::endMethod("CougarButton::update");
}

} /* namespace cougar */
