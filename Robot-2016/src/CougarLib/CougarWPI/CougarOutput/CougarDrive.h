/*
 * CougarDrive.h
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDRIVE_H_
#define SRC_COUGARLIB_COUGARDRIVE_H_

#include <memory>
#include "WPILib.h"
#include "CougarSpeedController.h"
#include "CougarSpeedControllerAggregate.h"
#include "../CougarHID/CougarJoystick.h"
#include "../../CougarDebug.h"

namespace cougar {


class CougarDrive {
public:
	CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right, std::string name);
	explicit CougarDrive(std::shared_ptr<CougarDrive> drive);
	explicit CougarDrive(const CougarDrive &drive);
	virtual ~CougarDrive();

	virtual void Drive(float outputMagnitude, float curve) const;
	virtual void TankDrive(std::shared_ptr<CougarJoystick> joystick, bool squaredInputs = true);
	virtual void ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick /* LEFT or RIGHT */ , bool squaredInputs = true);
	// I will implement more drive methods, e.g. mecanum, holonomic, if we decide to use them
	// But for right now, we rarely use anything else and I'm lazy

	// Just some happy little wrapper methods
	virtual void SetSensitivity(float sensitivity);
	virtual void SetMaxOutput(double maxOutput);
	virtual void SetExpiration(float timeout);
	virtual float GetExpiration() const;
	virtual bool IsAlive() const;
	virtual void StopMotor();
	virtual bool IsSafetyEnabled() const;
	virtual void SetSafetyEnabled(bool enabled);

	virtual std::string GetName() const;
	virtual const char *GetCName() const;

	enum ANALOG_STICKS {
		LEFT,
		RIGHT
	};
protected:
	class CougarDriveExtractor final {
		static std::shared_ptr<RobotDrive> ExtractDrive(std::shared_ptr<CougarDrive> drive);
		static std::shared_ptr<RobotDrive> ExtractDrive(const CougarDrive &drive);
	};
	friend CougarDriveExtractor;

	virtual std::shared_ptr<RobotDrive> GetDrive();
	virtual const bool GetSmoothing();
	virtual float speedFactor(std::shared_ptr<CougarJoystick> joystick);

	std::shared_ptr<RobotDrive> drive_;
	std::string name_;
	static const bool SMOOTHING = false;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
