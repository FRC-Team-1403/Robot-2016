/*
 * CougarDrive.h
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDRIVE_H_
#define SRC_COUGARLIB_COUGARDRIVE_H_

#include "WPILib.h"
#include "CougarSpeedControllerAggregate.h"
#include "CougarSpeedController.h"

namespace cougar {

class CougarDrive : public RobotDrive {
public:
	explicit CougarDrive(SpeedController *left, SpeedController *right);
	virtual ~CougarDrive();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDRIVE_H_ */
