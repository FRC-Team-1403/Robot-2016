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
	explicit CougarDrive(RobotDrive *drive) = delete;
	virtual ~CougarDrive();

	// Some method will be const because they are intended to be basic wrappers over RobotDrive.
	// The only thing they should be doing is calling the matching method on the drive_ object.

	virtual void Drive(float outputMagnitude, float curve) const;
	virtual void TankDrive(CougarJoystick *joystick, bool squaredInputs = true);
	virtual void ArcadeDrive(CougarJoystick *joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs = true);
	// I will implement more drive methods if we decide to use them
	// But for right now, we rarely use anything else and I'm lazy

	// Just a few wrapper methods
	virtual void SetSensitivity(float sensitivity) const;
	virtual void SetMaxOutput(double maxOutput) const;
	virtual void SetExpiration(float timeout) const;
	virtual float GetExpiration() const;
	virtual bool IsAlive() const;
	virtual void StopMotor() const;
	virtual bool IsSafetyEnabled() const;
	virtual void SetSafetyEnabled(bool enabled) const;

	enum ANALOG_STICKS {
		LEFT,
		RIGHT
	};
protected:

	float speedFactor(CougarJoystick *joystick);

	RobotDrive *drive_;
	static const bool SMOOTHING = false;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
