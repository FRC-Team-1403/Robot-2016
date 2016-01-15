/*
 * CougarDrive.h
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDRIVE_H_
#define SRC_COUGARLIB_COUGARDRIVE_H_

#include "WPILib.h"
#include "CougarSpeedController.h"
#include "CougarSpeedControllerAggregate.h"
#include "../CougarHID/CougarJoystick.h"
#include "../CougarDebug.h"

namespace cougar {


class CougarDrive {
public:
	explicit CougarDrive(SpeedController *left, SpeedController *right);
	virtual ~CougarDrive();

	virtual void TankDrive(CougarJoystick *joystick, bool squaredInputs = true);
	virtual void ArcadeDrive(CougarJoystick *joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs = true);

	enum ANALOG_STICKS {
		LEFT,
		RIGHT
	};
protected:

	double speedFactor(CougarJoystick *joystick);

	RobotDrive *drive_;
	static const bool SMOOTHING = false;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
