/*
 * CougarCommand.h
 *
 *  Created on: Mar 22, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_
#define SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_

#include "WPILib.h"
#include "CougarWPI/CougarHID/CougarJoystick.h"
#include "CougarDebug.h"

namespace cougar {

class CougarCommand : public Command {
public:

	CougarCommand(std::string name, std::shared_ptr<CougarJoystick> joy, bool isDefaultCommand = false, double timeout = -1.0);
	virtual ~CougarCommand();

protected:
	std::shared_ptr<CougarJoystick> joy_;

	virtual void stopAll() {}

private:
	virtual void interruptListener();

	bool doEndListener, isDefaultCommand_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_COUGARCOMMAND_H_ */
