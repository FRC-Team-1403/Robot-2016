/*
 * CougarSpeedControllerAggregate->cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedControllerAggregate.h"

namespace cougar {

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers, std::string name, bool inverted /* = false */) {
	this->controllers_ = controllers;
	this->name_ = name;
	this->inverted_ = inverted;
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s constructed", this->GetCName());
}

// Ignore warning about not initializing things in these constructors
CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers, const char *name, bool inverted /* = false */) {
	std::string tmpName(name);
	CougarSpeedControllerAggregate(controllers, tmpName, inverted);
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<CougarSpeedControllerAggregate> controllers) {
	CougarSpeedControllerAggregate(CougarSpeedControllerAggregateExtractor::extractControllers(controllers), controllers->GetName(), controllers->GetInverted());
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers) {
	CougarSpeedControllerAggregate(CougarSpeedControllerAggregateExtractor::extractControllers(controllers), controllers.GetName(), controllers.GetInverted());
}

CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate() {
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s destroyed", this->GetCName());
}


void CougarSpeedControllerAggregate::SetInverted(bool inverted) {
	this->inverted_ = inverted;
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
}

bool CougarSpeedControllerAggregate::GetInverted() const {
	return this->inverted_;
}

float CougarSpeedControllerAggregate::Sign() const {
	if (this->inverted_) {
		return -1.0;
	} else {
		return 1.0;
	}
}
float CougarSpeedControllerAggregate::GetCurrent() const {
	// TODO implement this properly
	return 0.0;
}
void CougarSpeedControllerAggregate::Set(float speed, uint8_t syncGroup/* = 0*/) {
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Set(speed);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s set to speed %f", this->GetCName(), speed);
}
float CougarSpeedControllerAggregate::Get() const {
	return this->controllers_->at(0)->Get(); // All CougarSpeedControllers should be at the same speed anyway, so just get the first one
}

void CougarSpeedControllerAggregate::Disable() {
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Disable();
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s disabled", this->GetCName());

}

void CougarSpeedControllerAggregate::PIDWrite(float output) {
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->PIDWrite(this->Sign() * output);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s...did something with PIDWrite. I don't actually know what that method does.", this->GetCName());

}

std::string CougarSpeedControllerAggregate::GetName() const {
	return this->name_;
}
const char *CougarSpeedControllerAggregate::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::extractControllers(std::shared_ptr<CougarSpeedControllerAggregate> controllers) {
	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> tmpControllers(controllers->getControllers());
	return tmpControllers;
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::extractControllers(const CougarSpeedControllerAggregate &controllers) {
	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> tmpControllers(controllers.getControllers());
	return tmpControllers;
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::getControllers() const {
	return this->controllers_;
}


} /* namespace cougar */
