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

	virtual void setSmoothingMode(int32_t mode);

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

	class Smoothing final {
	public:
		// TODO actually use this
		enum smoothingModes {
			NONE = -1,
			SINGLE_SINE = 0,
			TRIPLE_SINE = 1,
			BOUNDED_ACC = 2,
			SINGLE_SINE_BOUNDED_ACC = 3,
			TRIPLE_SINE_BOUNDED_ACC = 4
		};

		friend CougarJoystick;
	private:
		static float get(float a) {
			//Let's try some sine
			//Triple sine, in fact
			float vel;
			vel = sin(scale(a));
			vel = sin(scale(vel));
			vel = sin(scale(vel));
			return vel;
		}
		static float scale(float a) {
			float val = a * (M_PI / 2) * FACTOR;
			if (abs(val) > LIMIT) {
				val = LIMIT * (val / abs(val));
			}
			return val;
		}
	};

protected:

	uint32_t port;
	std::shared_ptr<Joystick> joystick_;
	static const bool SMOOTHING = true;
	static int SMOOTHING_MODE;
	static constexpr double FACTOR = 1.0;
	static constexpr double LIMIT = 1;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
