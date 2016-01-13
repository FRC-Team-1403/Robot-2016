/*
 * CougarSpeedControllerAggregate->cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarSpeedControllerAggregate.h"

namespace cougar {

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, std::string name, bool inverted/* = false*/) {
	this->controllers_ = controllers;
	this->name_ = name;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
}

CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, const char *name, bool inverted/* = false*/) {
	this->controllers_ = controllers;
	std::string tmpName(name);
	this->name_ = tmpName;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
}
CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, std::string name, bool inverted/* = false*/) {
	this->controllers_ = new std::vector<CougarSpeedController*>();
	for (uint32_t i = 0; i < count; i++) {
		this->controllers_->push_back(&controllers[i]);
	}
	this->name_ = name;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
}
CougarSpeedControllerAggregate::CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, const char *name, bool inverted/* = false*/) {
	this->controllers_ = new std::vector<CougarSpeedController*>();
	for (uint32_t i = 0; i < count; i++) {
		this->controllers_->push_back(&controllers[i]);
	}
	std::string tmpName(name);
	this->name_ = tmpName;
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
}

CougarSpeedControllerAggregate::~CougarSpeedControllerAggregate() {
	for (CougarSpeedController *controller : *this->controllers_) {
		delete controller;
	}
	delete this->controllers_;
}


void CougarSpeedControllerAggregate::SetInverted(bool inverted) {
	CougarDebug::debugPrinter("CougarSpeedController %s inversion set to %s", this->GetCName(), inverted ? "true" : "false");
	this->inverted_ = inverted;
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->SetInverted(this->inverted_);
	}
}

bool CougarSpeedControllerAggregate::GetInverted() const{
	return this->inverted_;
}

double CougarSpeedControllerAggregate::Sign() {
	if (this->inverted_) {
		return -1.0;
	} else {
		return 1.0;
	}
}
double CougarSpeedControllerAggregate::GetCurrent() {
	// TODO implement this properly
	return 0.0;
}
void CougarSpeedControllerAggregate::Set(float speed, uint8_t syncGroup/* = 0*/) {
	CougarDebug::debugPrinter("CougarSpeedControllerAggregate %s set to speed %f at time %f", this->GetCName(), speed, Timer::GetFPGATimestamp());
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->Set(speed);
	}
}
float CougarSpeedControllerAggregate::Get() const{
	return this->controllers_->at(0)->Get(); // All CougarSpeedControllers should be at the same speed anyway, so just get the first one
}

void CougarSpeedControllerAggregate::Disable() {
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->Disable();
	}
}

void CougarSpeedControllerAggregate::PIDWrite(float output) {
	for (CougarSpeedController *controller : *this->controllers_) {
		controller->PIDWrite(this->Sign() * output);
	}
}

std::string CougarSpeedControllerAggregate::GetName() {
	return this->name_;
}
const char *CougarSpeedControllerAggregate::GetCName() {
	return this->name_.c_str();
}


} /* namespace cougar */
