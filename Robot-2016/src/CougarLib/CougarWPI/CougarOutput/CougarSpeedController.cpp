/*
 * CougarSpeedController.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedController.h"

namespace cougar {

CougarSpeedController::CougarSpeedController(std::shared_ptr<SpeedController> controller, std::string name, uint32_t pdpSlot, bool inverted /* = false */) {
	this->controller_ = controller;
	this->name_ = name;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedController %s constructed", this->GetCName());
}

// Ignore warnings about not initializing things in these constructors
CougarSpeedController::CougarSpeedController(std::shared_ptr<SpeedController> controller, const char *name, uint32_t pdpSlot, bool inverted /* = false */) {
	std::string tmpName(name);
	CougarSpeedController(controller, tmpName, pdpSlot, inverted);
}

CougarSpeedController::CougarSpeedController(std::shared_ptr<CougarSpeedController> controller) {
	CougarSpeedController(CougarSpeedControllerExtractor::ExtractController(controller), controller->GetName(), CougarSpeedControllerExtractor::ExtractPDPSlot(controller), controller->GetInverted());
}

CougarSpeedController::CougarSpeedController(const CougarSpeedController &controller) {
	CougarSpeedController(CougarSpeedControllerExtractor::ExtractController(controller), controller.GetName(), CougarSpeedControllerExtractor::ExtractPDPSlot(controller), controller.GetInverted());
}

CougarSpeedController::~CougarSpeedController() {
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedController %s destroyed", this->GetCName());
}

void CougarSpeedController::SetInverted(bool inverted) {
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "SpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
	this->inverted_ = inverted;
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
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "SpeedController %s set to speed %f", this->GetCName(), speed);
	this->controller_->Set(speed);
}
float CougarSpeedController::Get() const {
	return this->controller_->Get();
}

void CougarSpeedController::Disable() {
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "SpeedController %s disabled", this->GetCName());
	this->controller_->Disable();
}

void CougarSpeedController::PIDWrite(float output) {
	this->controller_->PIDWrite(this->Sign() * output);
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedController %s...did something with PIDWrite. I don't actually know what that method does.", this->GetCName());
}

std::string CougarSpeedController::GetName() const {
	return this->name_;
}
const char *CougarSpeedController::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<SpeedController> CougarSpeedController::CougarSpeedControllerExtractor::ExtractController(std::shared_ptr<CougarSpeedController> controller) {
	return controller->GetController();
}

std::shared_ptr<SpeedController> CougarSpeedController::CougarSpeedControllerExtractor::ExtractController(const CougarSpeedController &controller) {
	return controller.GetController();
}

uint32_t CougarSpeedController::CougarSpeedControllerExtractor::ExtractPDPSlot(std::shared_ptr<CougarSpeedController> controller) {
	return controller->GetPDPSlot();
}

uint32_t CougarSpeedController::CougarSpeedControllerExtractor::ExtractPDPSlot(const CougarSpeedController &controller) {
	return controller.GetPDPSlot();
}

std::shared_ptr<SpeedController> CougarSpeedController::GetController() const {
	return this->controller_;
}

uint32_t CougarSpeedController::GetPDPSlot() const {
	return this->pdpSlot_;
}

}

