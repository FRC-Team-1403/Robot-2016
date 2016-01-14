/*
 * CougarSpeedController.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedController.h"

namespace cougar {

CougarSpeedController::CougarSpeedController(SpeedController *controller, std::string name, uint32_t pdpSlot, bool inverted/* = false*/) {
	this->controller_ = controller;
	this->name_ = name;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
}

CougarSpeedController::CougarSpeedController(SpeedController *controller, const char *name, uint32_t pdpSlot, bool inverted/* = false*/) {
	this->controller_ = controller;
	std::string tmpName(name);
	this->name_ = tmpName;
	this->pdpSlot_ = pdpSlot;
	this->inverted_ = inverted;
}

CougarSpeedController::~CougarSpeedController() {
	delete this->controller_;
}

void CougarSpeedController::SetInverted(bool inverted) {
	CougarDebug::debugPrinter("SpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
	this->inverted_ = inverted;
}

bool CougarSpeedController::GetInverted() const{
	return this->inverted_;
}

double CougarSpeedController::Sign() {
	if (this->inverted_) {
		return -1.0;
	} else {
		return 1.0;
	}
}
double CougarSpeedController::GetCurrent() {
	// TODO implement this properly
	return 0.0;
}
void CougarSpeedController::Set(float speed, uint8_t syncGroup/* = 0*/) {
	CougarDebug::debugPrinter("SpeedController %s set to speed %f at time %f", this->GetCName(), speed, Timer::GetFPGATimestamp());
	this->controller_->Set(speed);
}
float CougarSpeedController::Get() const{
	return this->controller_->Get();
}

void CougarSpeedController::Disable() {
	this->controller_->Disable();
}

void CougarSpeedController::PIDWrite(float output) {
	this->controller_->PIDWrite(this->Sign() * output);
}

std::string CougarSpeedController::GetName() {
	return this->name_;
}
const char *CougarSpeedController::GetCName() {
	return this->name_.c_str();
}

}

