/*
 * CougarController.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARCONTROLLER_H_
#define SRC_COUGARLIB_COUGARCONTROLLER_H_

#include "CougarDebug.h"

namespace cougar {

class CougarController {
protected:
	bool enabled = false;

public:
	explicit CougarController() {
		CougarDebug::debugPrinter("Started constructing CougarController object");
		CougarDebug::debugPrinter("Finished constructing CougarController object");
	}
	virtual ~CougarController() {
		CougarDebug::debugPrinter("Started destroying CougarController object");
		CougarDebug::debugPrinter("Finished destroying CougarController object");
	}

	virtual void update() = 0;
	virtual void reset() = 0;
	virtual double getGoal() = 0;

	virtual void enable() {
		CougarDebug::debugPrinter("CougarController::enable started");
		enabled = true;
		CougarDebug::debugPrinter("CougarController::enable finished");
	}

	virtual void disable() {
		CougarDebug::debugPrinter("CougarController::disable started");
		enabled = false;
		CougarDebug::debugPrinter("CougarController::disable finished");
	}

	virtual bool isEnabled() const {
		return enabled;
	}
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARCONTROLLER_H_ */
