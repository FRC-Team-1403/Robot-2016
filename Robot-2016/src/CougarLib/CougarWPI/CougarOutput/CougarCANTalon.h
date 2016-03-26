/*
 * CougarCANTalon.h
 *
 *	Created on: Feb 27, 2016
 *			Author: Thejas
 *
 *	Currently just a copy of CANTalon with some logging added in.
 *	Might do something more interesting with it if I have time.
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARCANTALON_H_
#define SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARCANTALON_H_

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2014-2016. All Rights Reserved.						  */
/* Open Source Software - may be modified and shared by FRC teams. The code	  */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.																  */
/*----------------------------------------------------------------------------*/

#include "WPILib.h"

#include "../../CougarDebug.h"
#include "../../CougarBase/Debuggable.h"

#include <memory>
#include <string>

namespace cougar {


class CougarCANTalon : public CANTalon,
					   public Debuggable {
 public:

	CougarCANTalon(int deviceNumber, std::string name) : CANTalon(deviceNumber), Debuggable(name) {}
	CougarCANTalon(int deviceNumber, int controlPeriodMs, std::string name)  : CANTalon(deviceNumber, controlPeriodMs), Debuggable(name) {}

	virtual ~CougarCANTalon() {}

	virtual std::string toString() override;
	virtual std::string dumpState() override;

	DISALLOW_COPY_AND_ASSIGN(CougarCANTalon);
};

} // namespace cougar

#endif /* SRC_COUGARLIB_COUGARWPI_COUGAROUTPUT_COUGARCANTALON_H_ */
