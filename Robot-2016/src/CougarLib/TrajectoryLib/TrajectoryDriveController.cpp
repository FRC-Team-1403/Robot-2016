/*
 * TrajectoryDriveController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: Thejas
 */

#include <CougarLib/TrajectoryLib/TrajectoryDriveController.h>
#include "../../Robot2016/Robot.h"


namespace cougar {

TrajectoryDriveController::TrajectoryDriveController() {
	CougarDebug::startMethod("TrajectoryDriveController::TrajectoryDriveController");
	followerLeft.reset(new TrajectoryFollower("left"));
	followerRight.reset(new TrajectoryFollower("right"));
	init();
	CougarDebug::endMethod("TrajectoryDriveController::TrajectoryDriveController");
}

bool TrajectoryDriveController::onTarget() {
	return followerLeft->isFinishedTrajectory();
}

void TrajectoryDriveController::loadProfile(std::shared_ptr<Trajectory> leftProfile,
		std::shared_ptr<Trajectory> rightProfile, double direction, double heading) {
	reset();
	followerLeft->setTrajectory(leftProfile);
	followerRight->setTrajectory(rightProfile);
	this->direction = direction;
	this->heading = heading;
}

void TrajectoryDriveController::loadProfileNoReset(std::shared_ptr<Trajectory> leftProfile,
		std::shared_ptr<Trajectory> rightProfile) {
	followerLeft->setTrajectory(leftProfile);
	followerRight->setTrajectory(rightProfile);
}

void TrajectoryDriveController::reset() {
	CougarDebug::startMethod("TrajectoryDriveController::reset");
		followerLeft->reset();
		followerRight->reset();
		Robot::driveTrain->resetEncoders();
	CougarDebug::endMethod("TrajectoryDriveController::reset");
}

int TrajectoryDriveController::getFollowerCurrentSegment() {
	return followerLeft->getCurrentSegment();
}

int TrajectoryDriveController::getNumSegments() {
	return followerLeft->getNumSegments();
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
		CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Distance Left: %f\tDistance Right: %f", distanceL, distanceR);

		double speedLeft = direction * followerLeft->calculate(distanceL);
		double speedRight = direction * followerRight->calculate(distanceR);
		CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Speed Left: %f\tSpeed Right: %f", speedLeft, speedRight);

		double goalHeading = followerLeft->getHeading();
		double observedHeading = Robot::driveTrain->getGyroAngleInRadians();
		CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Goal Heading: %f\tObserved Heading: %f", goalHeading, observedHeading);

		double angleDiffRads = CougarMath::getDifferenceInAngleRadians(observedHeading, goalHeading);
		double angleDiff = (angleDiffRads * 180) / M_PI;

		double turn = kTurn * angleDiff;

		CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Angle Difference: %f\tTurn: %f", angleDiff, turn);
		CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Is Finished: %d", this->onTarget());

		Robot::driveTrain->setLeftRightPower(speedLeft + turn, speedRight - turn);
	}
}

void TrajectoryDriveController::setTrajectory(std::shared_ptr<Trajectory> t) {
	this->trajectory = t;
}

double TrajectoryDriveController::getGoal() {
	return 0;
}

void TrajectoryDriveController::init() {
	followerLeft->configure(1, 0, 0.15, 1.0/9.0, 1.0/30.0);
	followerRight->configure(1, 0, 0.15, 1.0/9.0, 1.0/30.0);
}

} /* namespace cougar */
