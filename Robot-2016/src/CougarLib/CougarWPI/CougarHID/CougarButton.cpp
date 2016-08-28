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

void CougarButton::WhenPressed(Command *command) {
	CougarDebug::debugPrinter((std::string("CougarButton::WhenPressed [Command: ") + command->GetName() + "]").c_str());
	Button::WhenPressed(command);
	//CougarDebug::debugPrinter((std::string("CougarButton::WhenPressed [Command: ") + command->GetName() + "]").c_str());
}

void CougarButton::WhileHeld(Command *command) {
	CougarDebug::debugPrinter((std::string("CougarButton::WhileHeld [Command: ") + command->GetName() + "]").c_str());
	Button::WhileHeld(command);
	//CougarDebug::debugPrinter((std::string("CougarButton::WhileHeld [Command: ") + command->GetName() + "]").c_str());
}

void CougarButton::WhenReleased(Command *command) {
	CougarDebug::debugPrinter((std::string("CougarButton::WhenReleased [Command: ") + command->GetName() + "]").c_str());
	Button::WhenReleased(command);
	//CougarDebug::debugPrinter((std::string("CougarButton::WhenReleased [Command: ") + command->GetName() + "]").c_str());
}

void CougarButton::CancelWhenPressed(Command *command) {
	CougarDebug::debugPrinter((std::string("CougarButton::CancelWhenPressed [Command: ") + command->GetName() + "]").c_str());
	Button::CancelWhenPressed(command);
	///CougarDebug::debugPrinter((std::string("CougarButton::CancelWhenPressed [Command: ") + command->GetName() + "]").c_str());
}

void CougarButton::ToggleWhenPressed(Command *command) {
	CougarDebug::debugPrinter((std::string("CougarButton::ToggleWhenPressed [Command: ") + command->GetName() + "]").c_str());
	Button::ToggleWhenPressed(command);
	//CougarDebug::debugPrinter((std::string("CougarButton::ToggleWhenPressed [Command: ") + command->GetName() + "]").c_str());
}

} /* namespace cougar */
