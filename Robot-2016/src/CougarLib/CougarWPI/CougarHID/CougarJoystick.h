/*
 * CougarJoystick.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARJOYSTICK_H_
#define SRC_COUGARLIB_COUGARJOYSTICK_H_

#include <memory>
#include "WPILib.h"
#include "../../CougarDebug.h"

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
	virtual bool GetButtonStart();
	virtual bool GetButtonBack();

	virtual float GetStickLeftAxisX();
	virtual float GetStickLeftAxisY();
	virtual float GetStickRightAxisX();
	virtual float GetStickRightAxisY();
	virtual float GetRawAxis(uint32_t axis);
protected:

	class Accel final {
	public:
		Accel(uint32_t port) {
			port_ = port;
			vel_ = 0;
			time_ = Timer::GetFPGATimestamp();
		}

		float getVel(float a) {
			float accel_ = (vel_ - a) * FACTOR;
			double t = Timer::GetFPGATimestamp();
			double dt = t - time_;
			time_ = t;
			vel_ += accel_ * dt;
			if (accel_ > 0) {
				if (vel_ > accel_) {
					vel_ = accel_;
				}
			} else if (accel_ < 0) {
				if (vel_ < accel_) {
					vel_ = accel_;
				}
			}
			if (vel_ > LIMIT || vel_ < (LIMIT * -1)) {
				if (vel_ > 0) {
					vel_ = LIMIT;
				} else if (vel_< 0) {
					vel_ = LIMIT * -1;
				}
			}
			return vel_;
		}

	private:
		uint32_t port_;
		float vel_;
		double time_;
	};

	Accel *LX;
	Accel *LY;
	Accel *RX;
	Accel *RY;

	std::shared_ptr<Joystick> joystick_;
	static const bool SMOOTHING = false;
	static constexpr double FACTOR = 1.0;
	static constexpr double LIMIT = 0.5;


};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
