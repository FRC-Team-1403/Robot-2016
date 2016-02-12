/*
 * CougarSpeedControllerAggregate->cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedControllerAggregate.h"

namespace cougar {

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers, std::string name, bool inverted /* = false */) {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::CougarSpeedControllerAggregate " + name);
	this->controllers_ = controllers;
	this->name_ = name;
	this->inverted_ = inverted;
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	CougarDebug::endMethod("CougarSpeedControllerAggregate::CougarSpeedControllerAggregate " + this->GetName());
}

// Ignore warnings about not initializing things in these constructors

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<CougarSpeedControllerAggregate> controllers) :
		CougarSpeedControllerAggregate(CougarSpeedControllerAggregateExtractor::ExtractControllers(controllers), controllers->GetName(), controllers->GetInverted()){}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers) :
			CougarSpeedControllerAggregate(CougarSpeedControllerAggregateExtractor::ExtractControllers(controllers), controllers.GetName(), controllers.GetInverted()){}

CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate() {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate " + this->GetName());
	CougarDebug::endMethod("CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate " + this->GetName());
}


void CougarSpeedControllerAggregate::SetInverted(bool inverted) {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::SetInverted");
	this->inverted_ = inverted;
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
	CougarDebug::endMethod("CougarSpeedControllerAggregate::SetInverted");
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
	CougarDebug::startMethod("CougarSpeedControllerAggregate::Set");
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Set(speed);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s set to speed %f", this->GetCName(), speed);
	CougarDebug::endMethod("CougarSpeedControllerAggregate::Set");
}
float CougarSpeedControllerAggregate::Get() const {
	return this->controllers_->at(0)->Get(); // All CougarSpeedControllers should be at the same speed anyway, so just get the first one
}

void CougarSpeedControllerAggregate::Disable() {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::Disable");
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Disable();
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s disabled", this->GetCName());
	CougarDebug::endMethod("CougarSpeedControllerAggregate::Set");
}

void CougarSpeedControllerAggregate::PIDWrite(float output) {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::PIDWrite");
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->PIDWrite(this->Sign() * output);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s...did something with PIDWrite. I don't actually know what that method does.", this->GetCName());
	CougarDebug::endMethod("CougarSpeedControllerAggregate::PIDWrite");
}

std::string CougarSpeedControllerAggregate::GetName() const {
	return this->name_;
}
const char *CougarSpeedControllerAggregate::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::ExtractControllers(std::shared_ptr<CougarSpeedControllerAggregate> controllers) {
	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> tmpControllers(controllers->GetControllers());
	return tmpControllers;
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::ExtractControllers(const CougarSpeedControllerAggregate &controllers) {
	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> tmpControllers(controllers.GetControllers());
	return tmpControllers;
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::GetControllers() const {
	return this->controllers_;
}


} /* namespace cougar */
