/*
 * CougarCougarDoubleSolenoid.h
 *
 *	Created on: Mar 1, 2016
 *			Author: Thejas
 *
 *	Currently just a copy of CougarDoubleSolenoid with some logging added in.
 *	Might do something more interesting with it if I have time.
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARDOUBLESOLENOID_H_
#define SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARDOUBLESOLENOID_H_

#include "WPILib.h"

#include "SolenoidBase.h"
#include "LiveWindow/LiveWindowSendable.h"
#include "tables/ITableListener.h"
#include <memory>

#include "../../CougarBase/Debuggable.h"

#ifndef UINT32_MAX
#	define UINT32_MAX  (0xffffffff)
#endif

namespace cougar {

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.												*/
/* Open Source Software - may be modified and shared by FRC teams. The code	 */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.																															 */
/*----------------------------------------------------------------------------*/

/**
 * CougarDoubleSolenoid class for running 2 channels of high voltage Digital Output
 * (PCM).
 *
 * The CougarDoubleSolenoid class is typically used for pneumatics solenoids that
 * have two positions controlled by two separate channels.
 */
class CougarDoubleSolenoid : public SolenoidBase,
					   public LiveWindowSendable,
					   public ITableListener,
					   public Debuggable {
public:
	enum Value { kOff, kForward, kReverse };

	explicit CougarDoubleSolenoid(uint32_t forwardChannel, uint32_t reverseChannel, std::string name);
	CougarDoubleSolenoid(uint8_t moduleNumber, uint32_t forwardChannel,
								 uint32_t reverseChannel, std::string name);
	virtual ~CougarDoubleSolenoid();
	virtual void Set(Value value);
	virtual Value Get() const;
	bool IsFwdSolenoidBlackListed() const;
	bool IsRevSolenoidBlackListed() const;

	void ValueChanged(ITable* source, llvm::StringRef key,
										std::shared_ptr<nt::Value> value, bool isNew);
	void UpdateTable();
	void StartLiveWindowMode();
	void StopLiveWindowMode();
	std::string GetSmartDashboardType() const;
	void InitTable(std::shared_ptr<ITable> subTable);
	std::shared_ptr<ITable> GetTable() const;

	std::string toStringState();

	virtual std::string toString() override;
	virtual std::string dumpState() override;

private:
	uint32_t m_forwardChannel;	///< The forward channel on the module to control.
	uint32_t m_reverseChannel;	///< The reverse channel on the module to control.
	uint8_t m_forwardMask;			///< The mask for the forward channel.
	uint8_t m_reverseMask;			///< The mask for the reverse channel.

	std::shared_ptr<ITable> m_table;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARDOUBLESOLENOID_H_ */
