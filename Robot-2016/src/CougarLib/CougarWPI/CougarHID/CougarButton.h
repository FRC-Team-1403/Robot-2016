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

	CougarButton(std::shared_ptr<CougarJoystick> stick, uint32_t buttonPort);
	virtual ~CougarButton();

	bool getWasPressed();
	bool getWasReleased();
	bool get();
	void update();

private:
	bool wasPressed, wasReleased, isDown;
	std::shared_ptr<CougarJoystick> stick;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_ */
