/*
 * CougarDrive.h
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDRIVE_H_
#define SRC_COUGARLIB_COUGARDRIVE_H_

#include <memory>
#include <WPILib.h>
#include "CougarSpeedController.h"
#include "CougarSpeedControllerAggregate.h"
#include "../CougarHID/CougarJoystick.h"
#include "../../CougarDebug.h"

namespace cougar {


class CougarDrive {
public:
	CougarDrive(uint32_t leftPort, uint32_t rightPort,
			uint32_t leftPDPSlot, uint32_t rightPDPSlot, std::string name, bool reversed = false);
	CougarDrive(uint32_t leftPort1, uint32_t leftPort2,
			uint32_t rightPort1, uint32_t rightPort2,
			uint32_t leftPDPSlot1, uint32_t leftPDPSlot2,
			uint32_t rightPDPSlot1, uint32_t rightPDPSlot2,
			std::string name, bool reversed = false);
	CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right, std::string name, bool reversed = false);

	// TODO implement these constructors
	/*
	explicit CougarDrive(std::shared_ptr<CougarDrive> drive);
	explicit CougarDrive(const CougarDrive &drive);
	*/

	virtual ~CougarDrive();

	virtual void Drive(float outputMagnitude, float curve) const;
	virtual void TankDrive(float leftPower, float rightPower, bool squaredInputs = false);
	virtual void TankDrive(std::shared_ptr<CougarJoystick> joystick, bool squaredInputs = false);
	virtual void ArcadeDrive(float magnitude, float curve, bool squaredInputs = false);
	virtual void ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick = LEFT /*LEFT or RIGHT */, bool squaredInputs = false);
	// I will implement more drive methods, e.g. mecanum, holonomic, if we decide to use them
	// But for right now, we rarely use anything else and I'm lazy

	// Just some happy little wrapper methods
	virtual void SetSensitivity(float sensitivity);
	virtual void SetMaxOutput(double maxOutput);
	virtual void SetExpiration(float timeout);
	virtual float GetExpiration() const;
	virtual bool IsAlive() const;
	virtual void Stop();
	virtual bool IsSafetyEnabled() const;
	virtual void SetSafetyEnabled(bool enabled);

	virtual std::string GetName() const;
	virtual const char *GetCName() const;

	enum ANALOG_STICKS {
		LEFT,
		RIGHT
	};
protected:
	virtual std::shared_ptr<RobotDrive> GetDrive();

	std::shared_ptr<RobotDrive> drive_;
	std::string name_;
	int8_t reverse_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
