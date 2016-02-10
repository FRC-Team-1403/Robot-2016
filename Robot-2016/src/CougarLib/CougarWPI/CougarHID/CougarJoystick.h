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
#include <cmath>

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
	virtual bool GetRawButton(uint32_t port);

	virtual float GetStickLeftAxisX();
	virtual float GetStickLeftAxisY();
	virtual float GetStickRightAxisX();
	virtual float GetStickRightAxisY();
	virtual float GetRawAxis(uint32_t axis);
protected:

	class Smoothing final {
	public:
		static float get(float a) {
			//Let's try some sine
			//Triple sine, in fact
			float vel;
			vel = sin(scale(a));
			vel = sin(scale(vel));
			vel = sin(scale(vel));
			return vel;
		}

	private:
		static float scale(float a) {
			float val = a * (M_PI / 2) * FACTOR;
			if (abs(val) > LIMIT) {
				val = LIMIT * (val / abs(val));
			}
			return val;
		}
	};

	std::shared_ptr<Joystick> joystick_;
	static const bool SMOOTHING = false;
	static constexpr double FACTOR = 1.0;
	static constexpr double LIMIT = 0.5;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
