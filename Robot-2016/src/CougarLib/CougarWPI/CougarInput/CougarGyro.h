/*
 * CougarGyro.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 *
 *	Currently just a copy of AnalogGyro with some logging added in.
 *	Might do something more interesting with it if I have time.
 */

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_

#include "WPILib.h"
#include "CougarDebug.h"
#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"

namespace cougar {

class CougarGyro : public AnalogGyro, public Debuggable {
public:
	explicit CougarGyro(int32_t channel, std::string name);
	explicit CougarGyro(AnalogInput *channel, std::string name);
	explicit CougarGyro(std::shared_ptr<AnalogInput> channel, std::string name);
	CougarGyro(int32_t channel, uint32_t center, float offset, std::string name);
	CougarGyro(std::shared_ptr<AnalogInput> channel, uint32_t center, float offset, std::string name);
	virtual ~CougarGyro(){}

	virtual std::string toString() override;
	virtual std::string dumpState() override;

 protected:
	int32_t m_channel;

	DISALLOW_COPY_AND_ASSIGN(CougarGyro)
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_ */
