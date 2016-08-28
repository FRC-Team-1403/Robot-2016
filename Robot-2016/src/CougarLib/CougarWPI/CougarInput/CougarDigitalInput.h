/*
 * CougarDigitalInput.h
 *
 *  Created on: Mar 18, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARDIGITALINPUT_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARDIGITALINPUT_H_

#include "WPILib.h"
#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"

namespace cougar {

class CougarDigitalInput : public DigitalInput, public Debuggable {
public:
	explicit CougarDigitalInput(uint32_t channel, std::string name);
	virtual ~CougarDigitalInput();

	virtual std::string toString() override;
	virtual std::string dumpState() override;

	DISALLOW_COPY_AND_ASSIGN(CougarDigitalInput)
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARDIGITALINPUT_H_ */
