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
		Accel() {
			accel_ = 0;
			vel_ = 0;
			time_ = Timer::GetFPGATimestamp();
		}

		float getVel(float a) {
			double dt = Timer::GetFPGATimestamp() - time_;

		}

		float floor(float f) {

			//return f > LIMIT ? LIMIT : f;
		}
	private:
		float accel_;
		float vel_;
		double time_;
	};

	struct accelCurve {
		Accel LX();
		Accel LY();
		Accel RX();
		Accel RY();
	};

	std::shared_ptr<Joystick> joystick_;
	static const bool SMOOTHING = false;
	static const double FACTOR = 1.0;


};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARJOYSTICK_H_ */
