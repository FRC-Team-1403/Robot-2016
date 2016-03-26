/*
 * CougarSolenoid.cpp
 *
 *	Created on: Mar 1, 2016
 *			Author: Thejas
 */

#include "CougarSolenoid.h"
#include "WPIErrors.h"
#include "LiveWindow/LiveWindow.h"

#include <sstream>

namespace cougar {

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.												*/
/* Open Source Software - may be modified and shared by FRC teams. The code	 */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.																															 */
/*----------------------------------------------------------------------------*/



/**
 * Constructor using the default PCM ID (0).
 *
 * @param channel The channel on the PCM to control (0..7).
 */
CougarSolenoid::CougarSolenoid(uint32_t channel, std::string name)
		: CougarSolenoid(GetDefaultSolenoidModule(), channel, name) {}

/**
 * Constructor.
 *
 * @param moduleNumber The CAN ID of the PCM the solenoid is attached to
 * @param channel The channel on the PCM to control (0..7).
 */
CougarSolenoid::CougarSolenoid(uint8_t moduleNumber, uint32_t channel, std::string name)
		: Solenoid(moduleNumber, channel),
		  Debuggable(name) {
	m_channel = channel;
}

/**
 * Destructor.
 */
CougarSolenoid::~CougarSolenoid() {

}

std::string CougarSolenoid::toString() {
	std::string str = "CougarSolenoid " + this->name_ + "\n";
	str += "Channel: " + std::to_string(this->m_channel) + "\n";
	return str;
}

std::string CougarSolenoid::dumpState() {
	std::string str = this->toString();
	str += "State: " + std::to_string(this->Get()) + "\n";
	return str;
}

} /* namespace cougar */
