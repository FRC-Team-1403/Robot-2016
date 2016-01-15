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
		this->drive_->TankDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick), joystick->GetStickRightAxisY() * this->speedFactor(joystick), squaredInputs);
	}
}
void CougarDrive::ArcadeDrive(CougarJoystick *joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs /* = true */) {
	if (SMOOTHING) {
		// TODO: Implement input smoothing
	} else {
		if (stick == LEFT) {
			this->drive_->ArcadeDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick), joystick->GetStickLeftAxisX() * this->speedFactor(joystick), squaredInputs);
		} else if (stick == RIGHT) {
			this->drive_->ArcadeDrive(joystick->GetStickRightAxisY() * this->speedFactor(joystick), joystick->GetStickRightAxisX() * this->speedFactor(joystick), squaredInputs);
		} else {
			CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
			throw "An invalid analog stick has been specified...";
		}
	}
}

double CougarDrive::speedFactor(CougarJoystick *joystick) {
	const double SPEED_FACTOR = 0.5;
	return joystick->GetButtonY() ? SPEED_FACTOR : 1;
}

} /* namespace cougar */
