/*
 * CougarDrive.h
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 *
 *  TODO Make CougarDrive have an encoder and gyro
 */

#ifndef SRC_COUGARLIB_COUGARDRIVE_H_
#define SRC_COUGARLIB_COUGARDRIVE_H_

#include <memory>
#include <WPILib.h>
#include <cmath>
#include "CougarSpeedController.h"
#include "CougarSpeedControllerAggregate.h"
#include "../CougarHID/CougarJoystick.h"
#include "../../CougarDebug.h"
#include "../../CougarBase/Debuggable.h"
#include "../../CougarConstants.h"
#include "../CougarInput/CougarEncoder.h"

namespace cougar {

class CougarDrive : public Debuggable {

// Just go along with this
private:
	typedef void (CougarDrive::*drive_func)(std::shared_ptr<CougarJoystick>);

	// Quick wrappers since the drive selection functions
	// expect identical function signatures
	void InternalTankDrive(std::shared_ptr<CougarJoystick> joystick);
	void InternalArcadeDrive(std::shared_ptr<CougarJoystick> joystick);

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

	// I don't like this - it feels too hacky.
	// But until we add sensors to this class,
	// it's what we need to make this work
	virtual void LockDrive(std::shared_ptr<CougarEncoder> leftEncoder, std::shared_ptr<CougarEncoder> rightEncoder);

	// Not to be confused with anything autonomous-related
	// Automatically selects proper driving type and
	// locks the drive train when necessary
	// It's like magic - use it, make your life easier
	virtual void AutomaticDrive(std::shared_ptr<CougarJoystick> joystick, std::shared_ptr<CougarEncoder> leftEncoder, std::shared_ptr<CougarEncoder> rightEncoder);

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

	virtual std::string toString() override;
	virtual std::string dumpState() override;

	enum ANALOG_STICKS {
		LEFT,
		RIGHT
	};
protected:
	virtual drive_func DefaultDrive();
	virtual drive_func AltDrive();

	virtual std::shared_ptr<RobotDrive> GetDrive();

	typedef struct FPID_CONTROLLER {
		double setpoint_vel;
		double timeElapsed;
		double config_max_acc;
		double config_max_vel;
		double error_sum_;
		double goal_pos;
		double ka_;// @ full power ka = 0
		double kd_;
		double ki_;
		double kp_; //make really high and adjust as necessary. error is usually really small
		double kv_; // = 1/max velocity
		double last_error_;
		double next_state_acc;
		double next_state_pos;
		double next_state_vel;
		bool reset_;
		double setpoint_acc;
		double setpoint_pos;
	} FPID_CONTROLLER;

	virtual void configFPID();
	virtual double calculate(double position, FPID_CONTROLLER controller);

	FPID_CONTROLLER leftController;
	FPID_CONTROLLER rightController;
	FPID_CONTROLLER angleController;

	std::shared_ptr<RobotDrive> drive_;
	int8_t reverse_;

	DISALLOW_COPY_AND_ASSIGN(CougarDrive);
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
