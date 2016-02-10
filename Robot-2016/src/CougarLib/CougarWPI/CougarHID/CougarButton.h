/*
 * CougarButton.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_

#include "CougarJoystick.h"

namespace cougar {

class CougarButton {
public:

	uint32_t buttonPort;

	CougarButton(std::shared_ptr<CougarJoystick> stick, uint32_t buttonPort){
		this->stick = stick;
		this->buttonPort = buttonPort;
	}
	virtual ~CougarButton();

	bool getWasPressed() {
		return wasPressed;
	}

	bool getWasReleased() {
		return wasReleased;
	}

	bool get() {
		return isDown;
	}

	void update() {
		bool pressed = stick->GetRawButton(buttonPort);
		wasPressed = pressed && !isDown;
		wasReleased = !pressed && isDown;
		isDown = pressed;
	}

private:
	bool wasPressed, wasReleased, isDown;
	std::shared_ptr<CougarJoystick> stick;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_ */
