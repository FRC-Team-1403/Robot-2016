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

class CougarJoystick {
public:
	explicit CougarJoystick(uint32_t port);
	virtual ~CougarJoystick();

	virtual bool GetButtonA();
	virtual bool GetButtonB();
	virtual bool GetButtonX();
	virtual bool GetButtonY();
	virtual bool GetButtonRT();
	virtual bool GetButtonLT();
	virtual bool GetButtonRB();
	virtual bool GetButtonLB();
	virtual bool GetButtonDPADUp();
	virtual bool GetButtonDPADDown();
	virtual bool GetButtonDPADLeft();
	virtual bool GetButtonDPADRight();

	virtual double GetStickLeftAxisX();
	virtual double GetStickLeftAxisY();
	virtual double GetStickRightAxisX();
	virtual double GetStickRightAxisY();
protected:
	Joystick *joystick_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
