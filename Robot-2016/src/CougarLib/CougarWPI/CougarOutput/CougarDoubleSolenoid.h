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

#include "../../CougarBase/Debuggable.h"

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
class CougarDoubleSolenoid : public DoubleSolenoid,
					   public Debuggable {
public:

	CougarDoubleSolenoid(uint32_t forwardChannel, uint32_t reverseChannel, std::string name);
	CougarDoubleSolenoid(uint8_t moduleNumber, uint32_t forwardChannel,
								 uint32_t reverseChannel, std::string name);
	virtual ~CougarDoubleSolenoid();

	std::string toStringState();
	virtual std::string toString() override;
	virtual std::string dumpState() override;

private:
	// LOL variable shadowing
	uint32_t m_forwardChannel;	///< The forward channel on the module to control.
	uint32_t m_reverseChannel;	///< The reverse channel on the module to control.

	DISALLOW_COPY_AND_ASSIGN(CougarDoubleSolenoid);
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARDOUBLESOLENOID_H_ */
