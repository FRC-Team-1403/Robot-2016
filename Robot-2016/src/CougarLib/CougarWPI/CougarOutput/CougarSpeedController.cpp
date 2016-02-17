/*
 * CougarSpeedController.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedController.h"

namespace cougar {

CougarSpeedController::CougarSpeedController(uint32_t port, uint32_t pdpSlot, std::string name, bool inverted /* = false */) {
	CougarDebug::startMethod("CougarSpeedController::CougarSpeedController " + name);
	this->controller_.reset(new Victor(port));
	this->name_ = name;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
	CougarDebug::endMethod("CougarSpeedController::CougarSpeedController " + this->GetName());
}

CougarSpeedController::CougarSpeedController(std::shared_ptr<SpeedController> controller, uint32_t pdpSlot, std::string name, bool inverted /* = false */) {
	CougarDebug::startMethod("CougarSpeedController::CougarSpeedController " + name);
	this->controller_ = controller;
	this->name_ = name;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
	CougarDebug::endMethod("CougarSpeedController::CougarSpeedController " + this->GetName());
}

// Ignore warnings about not initializing things in these constructors

CougarSpeedController::CougarSpeedController(std::shared_ptr<CougarSpeedController> controller) :
		CougarSpeedController(controller->GetController(), controller->GetPDPSlot(), controller->GetName(), controller->GetInverted()){}

CougarSpeedController::CougarSpeedController(const CougarSpeedController &controller) :
		CougarSpeedController(controller.GetController(), controller.GetPDPSlot(), controller.GetName(), controller.GetInverted()){}

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
float CougarSpeedController::GetCurrent() const {
	// TODO implement this properly
	return 0.0;
}
void CougarSpeedController::Set(float speed, uint8_t syncGroup/* = 0*/) {
	//CougarDebug::startMethod("CougarSpeedController::Set " + this->GetName());
	this->controller_->Set(speed);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "SpeedController %s set to speed %f", this->GetCName(), speed);
	//CougarDebug::endMethod("CougarSpeedController::Set " + this->GetName());
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

std::shared_ptr<SpeedController> CougarSpeedController::GetController() const {
	return this->controller_;
}

}

