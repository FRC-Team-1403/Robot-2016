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
		: SolenoidBase(moduleNumber),
		  Debuggable(name),
		  m_channel(channel) {
	std::stringstream buf;
	if (!CheckSolenoidModule(m_moduleNumber)) {
		buf << "CougarSolenoid Module " << m_moduleNumber;
		wpi_setWPIErrorWithContext(ModuleIndexOutOfRange, buf.str());
		return;
	}
	if (!CheckSolenoidChannel(m_channel)) {
		buf << "CougarSolenoid Module " << m_channel;
		wpi_setWPIErrorWithContext(ChannelIndexOutOfRange, buf.str());
		return;
	}
	Resource::CreateResourceObject(m_allocated, m_maxModules * m_maxPorts);
	buf << "CougarSolenoid " << m_channel << " (Module: " << m_moduleNumber << ")";
	if (m_allocated->Allocate(m_moduleNumber * kSolenoidChannels + m_channel, buf.str()) == UINT32_MAX) {
		CloneError(*m_allocated);
		return;
	}

	LiveWindow::GetInstance()->AddActuator("CougarSolenoid", m_moduleNumber, m_channel, this);
	HALReport(HALUsageReporting::kResourceType_Solenoid, m_channel,
						m_moduleNumber);
}

/**
 * Destructor.
 */
CougarSolenoid::~CougarSolenoid() {
	if (CheckSolenoidModule(m_moduleNumber)) {
		m_allocated->Free(m_moduleNumber * kSolenoidChannels + m_channel);
	}
	if (m_table != nullptr) m_table->RemoveTableListener(this);
}

/**
 * Set the value of a solenoid.
 *
 * @param on Turn the solenoid output off or on.
 */
void CougarSolenoid::Set(bool on) {
	if (StatusIsFatal()) return;
	uint8_t value = on ? 0xFF : 0x00;
	uint8_t mask = 1 << m_channel;

	SolenoidBase::Set(value, mask, m_moduleNumber);
}

/**
 * Read the current value of the solenoid.
 *
 * @return The current value of the solenoid.
 */
bool CougarSolenoid::Get() const {
	if (StatusIsFatal()) return false;
	uint8_t value = GetAll(m_moduleNumber) & (1 << m_channel);
	return (value != 0);
}
/**
 * Check if solenoid is blacklisted.
 * 		If a solenoid is shorted, it is added to the blacklist and
 * 		disabled until power cycle, or until faults are cleared.
 * 		@see ClearAllPCMStickyFaults()
 *
 * @return If solenoid is disabled due to short.
 */
bool CougarSolenoid::IsBlackListed() const {
	int value = GetPCMSolenoidBlackList(m_moduleNumber) & (1 << m_channel);
	return (value != 0);
}

void CougarSolenoid::ValueChanged(ITable* source, llvm::StringRef key,
														std::shared_ptr<nt::Value> value, bool isNew) {
	if (!value->IsBoolean()) return;
	Set(value->GetBoolean());
}

void CougarSolenoid::UpdateTable() {
	if (m_table != nullptr) {
		m_table->PutBoolean("Value", Get());
	}
}

void CougarSolenoid::StartLiveWindowMode() {
	Set(false);
	if (m_table != nullptr) {
		m_table->AddTableListener("Value", this, true);
	}
}

void CougarSolenoid::StopLiveWindowMode() {
	Set(false);
	if (m_table != nullptr) {
		m_table->RemoveTableListener(this);
	}
}

std::string CougarSolenoid::GetSmartDashboardType() const { return "CougarSolenoid"; }

void CougarSolenoid::InitTable(std::shared_ptr<ITable> subTable) {
	m_table = subTable;
	UpdateTable();
}

std::shared_ptr<ITable> CougarSolenoid::GetTable() const { return m_table; }

std::string CougarSolenoid::toString() {
	std::string str = "CougarSolenoid " + this->name_ + "\n";
	str += "Channel: " + std::to_string(this->m_channel);
	return str;
}

std::string CougarSolenoid::dumpState() {
	std::string str = this->toString();
	str += "State: " + std::to_string(this->Get());
	return str;
}

} /* namespace cougar */
