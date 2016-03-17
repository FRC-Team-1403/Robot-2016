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

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.												*/
/* Open Source Software - may be modified and shared by FRC teams. The code	 */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.																															 */
/*----------------------------------------------------------------------------*/



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
		: SolenoidBase(moduleNumber),
		  Debuggable(name),
		  m_forwardChannel(forwardChannel),
		  m_reverseChannel(reverseChannel) {
	std::stringstream buf;
	if (!CheckSolenoidModule(m_moduleNumber)) {
		buf << "Solenoid Module " << m_moduleNumber;
		wpi_setWPIErrorWithContext(ModuleIndexOutOfRange, buf.str());
		return;
	}
	if (!CheckSolenoidChannel(m_forwardChannel)) {
		buf << "Solenoid Module " << m_forwardChannel;
		wpi_setWPIErrorWithContext(ChannelIndexOutOfRange, buf.str());
		return;
	}
	if (!CheckSolenoidChannel(m_reverseChannel)) {
		buf << "Solenoid Module " << m_reverseChannel;
		wpi_setWPIErrorWithContext(ChannelIndexOutOfRange, buf.str());
		return;
	}
	Resource::CreateResourceObject(
			m_allocated, m_maxModules * m_maxPorts);

	buf << "Solenoid " << m_forwardChannel << " (Module: " << m_moduleNumber
			<< ")";
	if (m_allocated->Allocate(
					m_moduleNumber * kSolenoidChannels + m_forwardChannel, buf.str()) ==
			UINT32_MAX) {
		CloneError(*m_allocated);
		return;
	}

	buf << "Solenoid " << m_reverseChannel << " (Module: " << m_moduleNumber
			<< ")";
	if (m_allocated->Allocate(
					m_moduleNumber * kSolenoidChannels + m_reverseChannel, buf.str()) ==
			UINT32_MAX) {
		CloneError(*m_allocated);
		return;
	}

	m_forwardMask = 1 << m_forwardChannel;
	m_reverseMask = 1 << m_reverseChannel;
	HALReport(HALUsageReporting::kResourceType_Solenoid, m_forwardChannel,
						m_moduleNumber);
	HALReport(HALUsageReporting::kResourceType_Solenoid, m_reverseChannel,
						m_moduleNumber);
	LiveWindow::GetInstance()->AddActuator("CougarDoubleSolenoid", m_moduleNumber,
																				 m_forwardChannel, this);
}

/**
 * Destructor.
 */
CougarDoubleSolenoid::~CougarDoubleSolenoid() {
	if (CheckSolenoidModule(m_moduleNumber)) {
		m_allocated->Free(m_moduleNumber * kSolenoidChannels + m_forwardChannel);
		m_allocated->Free(m_moduleNumber * kSolenoidChannels + m_reverseChannel);
	}
	if (m_table != nullptr) m_table->RemoveTableListener(this);
}

/**
 * Set the value of a solenoid.
 *
 * @param value The value to set (Off, Forward or Reverse)
 */
void CougarDoubleSolenoid::Set(Value value) {
	if (StatusIsFatal()) return;
	uint8_t rawValue = 0x00;

	switch (value) {
		case kOff:
			rawValue = 0x00;
			break;
		case kForward:
			rawValue = m_forwardMask;
			break;
		case kReverse:
			rawValue = m_reverseMask;
			break;
	}

	SolenoidBase::Set(rawValue, m_forwardMask | m_reverseMask, m_moduleNumber);
}

/**
 * Read the current value of the solenoid.
 *
 * @return The current value of the solenoid.
 */
CougarDoubleSolenoid::Value CougarDoubleSolenoid::Get() const {
	if (StatusIsFatal()) return kOff;
	uint8_t value = GetAll(m_moduleNumber);

	if (value & m_forwardMask) return kForward;
	if (value & m_reverseMask) return kReverse;
	return kOff;
}
/**
 * Check if the forward solenoid is blacklisted.
 * 		If a solenoid is shorted, it is added to the blacklist and
 * 		disabled until power cycle, or until faults are cleared.
 * 		@see ClearAllPCMStickyFaults()
 *
 * @return If solenoid is disabled due to short.
 */
bool CougarDoubleSolenoid::IsFwdSolenoidBlackListed() const {
	int blackList = GetPCMSolenoidBlackList(m_moduleNumber);
	return (blackList & m_forwardMask) ? 1 : 0;
}
/**
 * Check if the reverse solenoid is blacklisted.
 * 		If a solenoid is shorted, it is added to the blacklist and
 * 		disabled until power cycle, or until faults are cleared.
 * 		@see ClearAllPCMStickyFaults()
 *
 * @return If solenoid is disabled due to short.
 */
bool CougarDoubleSolenoid::IsRevSolenoidBlackListed() const {
	int blackList = GetPCMSolenoidBlackList(m_moduleNumber);
	return (blackList & m_reverseMask) ? 1 : 0;
}

void CougarDoubleSolenoid::ValueChanged(ITable* source, llvm::StringRef key,
																	std::shared_ptr<nt::Value> value,
																	bool isNew) {
	if (!value->IsString()) return;
	Value lvalue = kOff;
	if (value->GetString() == "Forward")
		lvalue = kForward;
	else if (value->GetString() == "Reverse")
		lvalue = kReverse;
	Set(lvalue);
}

void CougarDoubleSolenoid::UpdateTable() {
	if (m_table != nullptr) {
		m_table->PutString(
				"Value", (Get() == kForward ? "Forward"
																		: (Get() == kReverse ? "Reverse" : "Off")));
	}
}

void CougarDoubleSolenoid::StartLiveWindowMode() {
	Set(kOff);
	if (m_table != nullptr) {
		m_table->AddTableListener("Value", this, true);
	}
}

void CougarDoubleSolenoid::StopLiveWindowMode() {
	Set(kOff);
	if (m_table != nullptr) {
		m_table->RemoveTableListener(this);
	}
}

std::string CougarDoubleSolenoid::GetSmartDashboardType() const {
	return "Double Solenoid";
}

void CougarDoubleSolenoid::InitTable(std::shared_ptr<ITable> subTable) {
	m_table = subTable;
	UpdateTable();
}

std::shared_ptr<ITable> CougarDoubleSolenoid::GetTable() const { return m_table; }

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
	str += "Forward Channel: " + std::to_string(this->m_forwardChannel);
	str += "Reverse Channel: " + std::to_string(this->m_reverseChannel);
	return str;
}

std::string CougarDoubleSolenoid::dumpState() {
	std::string str = this->toString();
	str += "State: " + this->toStringState();
	return str;
}

} /* namespace cougar */
