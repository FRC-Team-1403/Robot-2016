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
	explicit CougarJoystick(uint32_t port, int smoothingMode = Smoothing::TRIPLE_SINE, bool ignoreModsExceptSmoothing = false);
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
			return a * (M_PI / 2);
		}
	};

protected:

	float getAxis(uint32_t axis);

	uint32_t port_;
	std::shared_ptr<Joystick> joystick_;
	bool ignoreMods_;
	static const bool SMOOTHING = true;
	static int SMOOTHING_MODE;
	static constexpr double SCALING_FACTOR = 0.75;
	static constexpr double LIMIT = 1;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
