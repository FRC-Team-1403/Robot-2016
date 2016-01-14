/*
 * CougarJoystick.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarJoystick.h"

namespace cougar {

CougarJoystick::CougarJoystick(uint32_t port) {
	this->joystick_ = new Joystick(port);

}

CougarJoystick::~CougarJoystick() {
	delete this->joystick_;
}

} /* namespace cougar */
