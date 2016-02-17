/*
 * CougarSpeedControllerAggregate->cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedControllerAggregate.h"

namespace cougar {

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(uint32_t port1, uint32_t port2,
		uint32_t PDPSlot1, uint32_t PDPSlot2, std::string name, bool inverted /* = false */) {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::CougarSpeedControllerAggregate " + name);
	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> tmpControllers(new std::vector<std::shared_ptr<CougarSpeedController>>);
	tmpControllers->push_back(std::shared_ptr<CougarSpeedController>(new CougarSpeedController(port1, PDPSlot1, name + "1")));
	tmpControllers->push_back(std::shared_ptr<CougarSpeedController>(new CougarSpeedController(port2, PDPSlot2, name + "2")));
	this->controllers_ = tmpControllers;
	this->name_ = name;
	this->inverted_ = inverted;
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	CougarDebug::endMethod("CougarSpeedControllerAggregate::CougarSpeedControllerAggregate " + this->GetName());
}

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

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::shared_ptr<CougarSpeedControllerAggregate> controllers) :
		CougarSpeedControllerAggregate(controllers->GetControllers(), controllers->GetName(), controllers->GetInverted()){}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers) :
			CougarSpeedControllerAggregate(controllers.GetControllers(), controllers.GetName(), controllers.GetInverted()){}

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
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarSpeedControllerAggregate %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
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
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Set(speed);
	}
	CougarDebug::debugPrinter(CougarDebug::UNIMPORTANT, "CougarSpeedControllerAggregate %s set to speed %f", this->GetCName(), speed);
}

void CougarSpeedControllerAggregate::StopMotor() {
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Set(0);
	}
}

float CougarSpeedControllerAggregate::Get() const {
	return this->controllers_->at(0)->Get(); // All CougarSpeedControllers should be at the same speed anyway, so just get the first one
}

void CougarSpeedControllerAggregate::Disable() {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::Disable");
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->Disable();
	}
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarSpeedControllerAggregate %s disabled", this->GetCName());
	CougarDebug::endMethod("CougarSpeedControllerAggregate::Set");
}

void CougarSpeedControllerAggregate::PIDWrite(float output) {
	CougarDebug::startMethod("CougarSpeedControllerAggregate::PIDWrite");
	for (std::shared_ptr<CougarSpeedController> controller : *this->controllers_) {
		controller->PIDWrite(this->Sign() * output);
	}
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarSpeedControllerAggregate %s...did something with PIDWrite. I don't actually know what that method does.", this->GetCName());
	CougarDebug::endMethod("CougarSpeedControllerAggregate::PIDWrite");
}

std::string CougarSpeedControllerAggregate::GetName() const {
	return this->name_;
}
const char *CougarSpeedControllerAggregate::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> CougarSpeedControllerAggregate::GetControllers() const {
	return this->controllers_;
}


} /* namespace cougar */
