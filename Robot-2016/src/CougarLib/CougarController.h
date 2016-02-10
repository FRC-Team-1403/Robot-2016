/*
 * CougarController.h
 *
 *  Created on: Feb 9, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARCONTROLLER_H_
#define SRC_COUGARLIB_COUGARCONTROLLER_H_

namespace cougar {

class CougarController {
protected:
	bool enabled = false;

public:
	  virtual void update() = 0;
	  virtual void reset() = 0;
	  virtual double getGoal() = 0;

	  void enable() {
	    enabled = true;
	  }

	  void disable() {
	    enabled = false;
	  }

	  bool isEnabled() {
	    return enabled;
	  }
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARCONTROLLER_H_ */
