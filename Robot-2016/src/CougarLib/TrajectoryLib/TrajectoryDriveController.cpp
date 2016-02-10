/*
 * TrajectoryDriveController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: Thejas
 */

#include <CougarLib/TrajectoryLib/TrajectoryDriveController.h>
#include "../../Robot2016/Robot.h"


namespace cougar {

TrajectoryDriveController::TrajectoryDriveController() : CougarController() {
	followerLeft.reset(new TrajectoryFollower("left"));
	followerRight.reset(new TrajectoryFollower("right"));
	init();
}

void TrajectoryDriveController::reset() {
		followerLeft->reset();
		followerRight->reset();
		Robot::driveTrain->resetEncoders();
	}

void TrajectoryDriveController::update() {
		if (!enabled) {
			return;
		}

		if (onTarget()) {
			Robot::driveTrain->setLeftRightPower(0.0, 0.0);
		} else	{
			double distanceL = direction * Robot::driveTrain->getLeftEncoderDistance();
			double distanceR = direction * Robot::driveTrain->getRightEncoderDistance();

			double speedLeft = direction * followerLeft->calculate(distanceL);
			double speedRight = direction * followerRight->calculate(distanceR);

			double goalHeading = followerLeft->getHeading();
			double observedHeading = Robot::driveTrain->getGyroAngleInRadians();

			double angleDiffRads = CougarMath::getDifferenceInAngleRadians(observedHeading, goalHeading);
			double angleDiff = (angleDiffRads * 180) / M_PI;

			double turn = kTurn * angleDiff;
			Robot::driveTrain->setLeftRightPower(speedLeft + turn, speedRight - turn);
		}
	}

} /* namespace cougar */
