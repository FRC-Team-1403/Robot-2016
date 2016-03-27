/*
 * CougarButton.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_

#include "WPILib.h"
#include "CougarJoystick.h"
#include "../../CougarDebug.h"

namespace cougar {

class CougarButton : public Button {
public:

	uint32_t buttonPort;

	CougarButton(std::shared_ptr<CougarJoystick> stick, uint32_t buttonPort);
	virtual ~CougarButton();

	virtual bool getWasPressed();
	virtual bool getWasReleased();
	virtual bool Get() override;
	virtual void update();

	virtual void WhenPressed(Command *command) override;
	virtual void WhileHeld(Command *command) override;
	virtual void WhenReleased(Command *command) override;
	virtual void CancelWhenPressed(Command *command) override;
	virtual void ToggleWhenPressed(Command *command) override;

private:
	bool wasPressed_, wasReleased_, isDown_;
	std::shared_ptr<CougarJoystick> stick_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARHID_COUGARBUTTON_H_ */
