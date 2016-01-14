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

void CougarDrive::TankDrive(CougarJoystick *joystick, bool squaredInputs /* = true */) {
	if (SMOOTHING) {
		// TODO: Implement input smoothing
	} else {
		this->drive_->TankDrive(joystick->GetStickLeftAxisY(), joystick->GetStickRightAxisY(), squaredInputs);
	}
}
void CougarDrive::ArcadeDrive(CougarJoystick *joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs /* = true */) {
	if (SMOOTHING) {
			// TODO: Implement input smoothing
		} else {
			if (stick == LEFT) {
				this->drive_->ArcadeDrive(joystick->GetStickLeftAxisY(), joystick->GetStickLeftAxisX(), squaredInputs);
			} else if (stick == RIGHT) {
				this->drive_->ArcadeDrive(joystick->GetStickRightAxisY(), joystick->GetStickRightAxisX(), squaredInputs);
			} else {
				CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
				throw "An invalid analog stick has been specified...";
			}
		}
}

} /* namespace cougar */
