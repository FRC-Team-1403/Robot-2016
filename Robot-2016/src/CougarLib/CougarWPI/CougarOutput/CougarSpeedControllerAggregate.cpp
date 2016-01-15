/*
 * CougarSpeedControllerAggregate->cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedControllerAggregate.h"

namespace cougar {

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, std::string name, bool inverted /* = false */) {
	this->controllers_ = controllers;
	this->name_ = name;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	this->shouldDelete_ = false;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s constructed", this->GetCName());
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, const char *name, bool inverted /* = false */) {
	this->controllers_ = controllers;
	std::string tmpName(name);
	this->name_ = tmpName;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	this->shouldDelete_ = false;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s constructed", this->GetCName());
}
CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, std::string name, bool inverted /* = false */) {
	this->controllers_ = new std::vector<CougarSpeedController*>();
	for (uint32_t i = 0; i < count; i++) {
		this->controllers_->push_back(new CougarSpeedController(controllers[i]));
	}
	this->name_ = name;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	this->shouldDelete_ = true;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s constructed", this->GetCName());
}
CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, const char *name, bool inverted /* = false */) {
	this->controllers_ = new std::vector<CougarSpeedController*>();
	for (uint32_t i = 0; i < count; i++) {
		this->controllers_->push_back(new CougarSpeedController(controllers[i]));
	}
	std::string tmpName(name);
	this->name_ = tmpName;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
	this->shouldDelete_ = true;
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s constructed", this->GetCName());
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(CougarSpeedControllerAggregate *controllers) {
	this->controllers_ = CougarSpeedControllerAggregateExtractor::extractControllers(controllers);
	this->name_ = controllers->GetName();
	this->inverted_ = controllers->GetInverted();
	this->shouldDelete_ = false;
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers) {
	this->controllers_ = CougarSpeedControllerAggregateExtractor::extractControllers(controllers);
	this->name_ = controllers.GetName();
	this->inverted_ = controllers.GetInverted();
	this->shouldDelete_ = false;
}

CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate() {
	if (this->shouldDelete_) {
		delete this->controllers_;
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s destroyed", this->GetCName());
}


void CougarSpeedControllerAggregate::SetInverted(bool inverted) {
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
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
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->Set(speed);
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s set to speed %f", this->GetCName(), speed);
}
float CougarSpeedControllerAggregate::Get() const {
	return this->controllers_->at(0)->Get(); // All CougarSpeedControllers should be at the same speed anyway, so just get the first one
}

void CougarSpeedControllerAggregate::Disable() {
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->Disable();
	}
	CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::MESSAGE, "CougarSpeedControllerAggregate %s disabled", this->GetCName());

}

void CougarSpeedControllerAggregate::PIDWrite(float output) {
	for (CougarSpeedController *controller : *this->controllers_) {
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

std::vector<CougarSpeedController*> *CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::extractControllers(CougarSpeedControllerAggregate *controllers) {
	return new std::vector<CougarSpeedController*>(controllers->getControllers());
}

std::vector<CougarSpeedController*> *CougarSpeedControllerAggregate::CougarSpeedControllerAggregateExtractor::extractControllers(const CougarSpeedControllerAggregate &controllers) {
	return new std::vector<CougarSpeedController*>(controllers.getControllers());
}

std::vector<CougarSpeedController*> *CougarSpeedControllerAggregate::getControllers() const {
	return this->controllers_;
}


} /* namespace cougar */
