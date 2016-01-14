/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(SpeedController *left, SpeedController *right) :
		RobotDrive(left, right){

}

CougarDrive::CougarDrive(CougarSpeedController *left, CougarSpeedController *right) :
		RobotDrive((SpeedController *)left, (SpeedController *)right){

}

CougarDrive::CougarDrive(CougarSpeedControllerAggregate *left, CougarSpeedControllerAggregate *right) :
		RobotDrive((SpeedController *)left, (SpeedController *)right){

}

CougarDrive::~CougarDrive() {

}

} /* namespace cougar */
