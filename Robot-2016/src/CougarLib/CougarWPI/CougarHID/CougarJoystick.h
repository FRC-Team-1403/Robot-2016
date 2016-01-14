/*
 * CougarJoystick.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARJOYSTICK_H_
#define SRC_COUGARLIB_COUGARJOYSTICK_H_

#include "WPILib.h"

namespace cougar {

class CougarJoystick : public Joystick{
public:
	CougarJoystick(uint32_t port);
	virtual ~CougarJoystick();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
