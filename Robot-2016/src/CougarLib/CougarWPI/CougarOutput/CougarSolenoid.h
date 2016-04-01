/*
 * CougarSolenoid.h
 *
 *	Created on: Mar 1, 2016
 *			Author: Thejas
 *
 *	Currently just a copy of Solenoid with some logging added in.
 *	Might do something more interesting with it if I have time.
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARSOLENOID_H_
#define SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARSOLENOID_H_

#include "WPILib.h"
#include <memory>

#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"


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
 * CougarSolenoid class for running high voltage Digital Output (PCM).
 *
 * The CougarSolenoid class is typically used for pneumatics solenoids, but could be
 * used
 * for any device within the current spec of the PCM.
 */
class CougarSolenoid : public Solenoid,
					   public Debuggable {
public:
	CougarSolenoid(uint32_t channel, std::string name);
	CougarSolenoid(uint8_t moduleNumber, uint32_t channel, std::string name);
	virtual ~CougarSolenoid();

	virtual std::string toString() override;
	virtual std::string dumpState() override;

private:
	// LOL variable shadowing
	uint32_t m_channel;	///< The channel on the module to control.

	DISALLOW_COPY_AND_ASSIGN(CougarSolenoid)
};
} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARSOLENOID_H_ */
