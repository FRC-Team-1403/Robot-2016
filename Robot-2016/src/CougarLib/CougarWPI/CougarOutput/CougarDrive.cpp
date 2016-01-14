/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(SpeedController *left, SpeedController *right) {
	this->drive_ = new RobotDrive(left, right);
}

CougarDrive::~CougarDrive() {
	delete this->drive_;
}

} /* namespace cougar */
