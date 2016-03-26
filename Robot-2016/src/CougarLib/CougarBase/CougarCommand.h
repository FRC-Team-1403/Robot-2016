/*
 * CougarCommand.h
 *
 *  Created on: Mar 22, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_
#define SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_

#include "WPILib.h"
#include "../CougarWPI/CougarHID/CougarJoystick.h"

namespace cougar {

class CougarCommand : public Command {
public:

	typedef bool (CougarJoystick::*JoyInterruptFn)();

	CougarCommand(std::string name, std::shared_ptr<CougarJoystick> joy, JoyInterruptFn interruptFn, double timeout = -1.0);
	virtual ~CougarCommand();

protected:
	std::shared_ptr<CougarJoystick> joy_;
	JoyInterruptFn interruptFn_;

	virtual void stopAll() = 0;

private:
	virtual void interruptListener();

	bool doEndListener;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_ */
