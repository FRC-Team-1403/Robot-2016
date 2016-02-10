/*
 * CougarButton.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_

#include "CougarJoystick.h"
#include "../../CougarDebug.h"

namespace cougar {

class CougarButton {
public:

	uint32_t buttonPort;

	CougarButton(std::shared_ptr<CougarJoystick> stick, uint32_t buttonPort){
		CougarDebug::debugPrinter("Started constructing CougarButton object with port %d", buttonPort);
		this->stick = stick;
		this->buttonPort = buttonPort;
		this->isDown = stick->GetRawButton(buttonPort);
		update();
		CougarDebug::debugPrinter("Finished constructing CougarButton object with port %d", buttonPort);
	}
	virtual ~CougarButton() {
		CougarDebug::debugPrinter("Started destroying CougarButton object with port %d", buttonPort);
		CougarDebug::debugPrinter("Finished destroying CougarButton object with port %d", buttonPort);
	}

	bool getWasPressed() {
		update();
		return wasPressed;
	}

	bool getWasReleased() {
		update();
		return wasReleased;
	}

	bool get() {
		update();
		return isDown;
	}

	void update() {
		CougarDebug::debugPrinter("CougarButton::update started");
		bool pressed = stick->GetRawButton(buttonPort);
		wasPressed = pressed && !isDown;
		wasReleased = !pressed && isDown;
		isDown = pressed;
		CougarDebug::debugPrinter("CougarButton::update finished");
	}

private:
	bool wasPressed, wasReleased, isDown;
	std::shared_ptr<CougarJoystick> stick;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_ */
