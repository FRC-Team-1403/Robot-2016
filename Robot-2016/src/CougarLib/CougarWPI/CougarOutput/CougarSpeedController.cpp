/*
 * CougarSpeedController.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedController.h"

namespace cougar {

CougarSpeedController::CougarSpeedController(uint32_t port, uint32_t pdpSlot,
		std::string name, bool inverted /* = false */) : Debuggable(name) {
	CougarDebug::startMethod("CougarSpeedController::CougarSpeedController " + name);
	this->controller_.reset(new Victor(port));
	this->port_ = port;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
	CougarDebug::endMethod("CougarSpeedController::CougarSpeedController " + this->GetName());
}

CougarSpeedController::CougarSpeedController(std::shared_ptr<SpeedController> controller, uint32_t pdpSlot,
		std::string name, bool inverted /* = false */) : Debuggable(name) {
	CougarDebug::startMethod("CougarSpeedController::CougarSpeedController " + name);
	this->controller_ = controller;
	this->port_ = -1;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
	CougarDebug::endMethod("CougarSpeedController::CougarSpeedController " + this->GetName());
}

CougarSpeedController::~CougarSpeedController() {
	CougarDebug::startMethod("CougarSpeedController::~CougarSpeedController " + this->GetName());
	CougarDebug::endMethod("CougarSpeedController::~CougarSpeedController " + this->GetName());
}

void CougarSpeedController::SetInverted(bool inverted) {
	CougarDebug::startMethod("CougarSpeedController::SetInverted " + this->GetName());
	this->inverted_ = inverted;
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "SpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
	CougarDebug::endMethod("CougarSpeedController::SetInverted " + this->GetName());
}

bool CougarSpeedController::GetInverted() const {
	return this->inverted_;
}

float CougarSpeedController::Sign() const {
	if (this->inverted_) {
		return -1.0;
	} else {
		return 1.0;
	}
}

void CougarSpeedController::Set(float speed, uint8_t syncGroup/* = 0*/) {
	this->controller_->Set(speed);
}

void CougarSpeedController::StopMotor() {
	this->Set(0);
}

float CougarSpeedController::Get() const {
	return this->controller_->Get();
}

void CougarSpeedController::Disable() {
	CougarDebug::startMethod("CougarSpeedController::Disable " + this->GetName());
	this->controller_->Disable();
	CougarDebug::endMethod("CougarSpeedController::Disable " + this->GetName());
}

void CougarSpeedController::PIDWrite(float output) {
	CougarDebug::startMethod("CougarSpeedController::PIDWrite " + this->GetName());
	this->controller_->PIDWrite(this->Sign() * output);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarSpeedController %s...did something with PIDWrite. I don't actually know what that method does.", this->GetCName());
	CougarDebug::endMethod("CougarSpeedController::PIDWrite " + this->GetName());
}

std::string CougarSpeedController::GetName() const {
	return this->name_;
}
const char *CougarSpeedController::GetCName() const {
	return this->name_.c_str();
}

uint32_t CougarSpeedController::GetPDPSlot() const {
	return this->pdpSlot_;
}

std::string CougarSpeedController::toString() {
	std::string str = "CougarSpeedController " + this->name_ + "\n";
	return str;
}

std::string CougarSpeedController::dumpState() {
	std::string str = this->toString();
	str += "Port: " + std::to_string(this->port_) + "\n";
	str += "PDP Slot: " + std::to_string(this->pdpSlot_) + "\n";
	str += "Inverted: " + std::to_string(this->inverted_) + "\n";
	str += "Set Power: " + std::to_string(this->controller_->Get()) + "\n";
	return str;
}

std::shared_ptr<SpeedController> CougarSpeedController::GetController() const {
	return this->controller_;
}

}

