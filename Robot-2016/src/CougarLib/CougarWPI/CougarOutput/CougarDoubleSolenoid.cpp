/*
 * CougarDoubleSolenoid.cpp
 *
 *	Created on: Mar 1, 2016
 *			Author: Thejas
 */

#include "CougarDoubleSolenoid.h"
#include "WPIErrors.h"
#include "LiveWindow/LiveWindow.h"

#include <sstream>

namespace cougar {

/**
 * Constructor.
 * Uses the default PCM ID of 0
 * @param forwardChannel The forward channel number on the PCM (0..7).
 * @param reverseChannel The reverse channel number on the PCM (0..7).
 */
CougarDoubleSolenoid::CougarDoubleSolenoid(uint32_t forwardChannel, uint32_t reverseChannel, std::string name)
		: CougarDoubleSolenoid(GetDefaultSolenoidModule(), forwardChannel, reverseChannel, name) {}

/**
 * Constructor.
 *
 * @param moduleNumber The CAN ID of the PCM.
 * @param forwardChannel The forward channel on the PCM to control (0..7).
 * @param reverseChannel The reverse channel on the PCM to control (0..7).
 */
CougarDoubleSolenoid::CougarDoubleSolenoid(uint8_t moduleNumber, uint32_t forwardChannel,
										   uint32_t reverseChannel, std::string name)
		: DoubleSolenoid(moduleNumber, forwardChannel, reverseChannel),
		  Debuggable(name) {
	this->m_forwardChannel = forwardChannel;
	this->m_reverseChannel = reverseChannel;
}

/**
 * Destructor.
 */
CougarDoubleSolenoid::~CougarDoubleSolenoid() {

}

std::string CougarDoubleSolenoid::toStringState() {
	switch (this->Get()) {
	case kOff:
		return "kOff";
	case kForward:
		return "kForward";
	case kReverse:
		return "kReverse";
	default:
		return "IDK";
	}
}

std::string CougarDoubleSolenoid::toString() {
	std::string str = "CougarSolenoid " + this->name_ + "\n";
	str += "Forward Channel: " + std::to_string(this->m_forwardChannel) + "\n";
	str += "Reverse Channel: " + std::to_string(this->m_reverseChannel) + "\n";
	return str;
}

std::string CougarDoubleSolenoid::dumpState() {
	std::string str = this->toString();
	str += "State: " + this->toStringState();
	return str;
}

} /* namespace cougar */
