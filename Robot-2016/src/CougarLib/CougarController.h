/*
 * CougarController.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 *
 * Inspired by Team 254
 * Thank you to the Cheesy Poofs for open-sourcing their code.
 *
 */

#ifndef SRC_COUGARLIB_COUGARCONTROLLER_H_
#define SRC_COUGARLIB_COUGARCONTROLLER_H_

#include "CougarDebug.h"

namespace cougar {

class CougarController {
protected:
	bool enabled = false;

public:
	explicit CougarController();
	virtual ~CougarController();

	virtual void enable();
	virtual void disable();
	virtual bool isEnabled() const;

	virtual void update() = 0;
	virtual void reset() = 0;
	virtual double getGoal() = 0;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARCONTROLLER_H_ */
