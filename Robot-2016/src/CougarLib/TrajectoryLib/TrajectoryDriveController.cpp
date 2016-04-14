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
		double distanceR = direction * Robot::driveTrain->getLeftEncoderDistance();
		double distanceL = -1 * direction * Robot::driveTrain->getRightEncoderDistance();
		CougarDebug::debugPrinter("Distance Left: %f", distanceL);
		CougarDebug::debugPrinter("Distance Right: %f", distanceR);

		double speedLeft = direction * followerLeft->calculate(distanceL);
		double speedRight = direction * followerRight->calculate(distanceR);
		CougarDebug::debugPrinter("Speed Left: %f", speedLeft);
		CougarDebug::debugPrinter("Speed Right: %f", speedRight);

		double goalHeading = followerLeft->getHeading();
		double observedHeading = Robot::driveTrain->getGyroAngleInRadians();
		CougarDebug::debugPrinter("Observed Heading: %f", observedHeading);
		CougarDebug::debugPrinter("Goal Heading: %f", goalHeading);

		double angleDiffRads = CougarMath::getDifferenceInAngleRadians(observedHeading, goalHeading);
		double angleDiff = (angleDiffRads * 180) / M_PI;

		double turn = kTurn * angleDiff;

		CougarDebug::debugPrinter("Angle Difference: %f", angleDiffRads, turn);
		CougarDebug::debugPrinter("Turn: %f", turn);
		CougarDebug::debugPrinter("Is Finished: %d", this->onTarget());

		Robot::driveTrain->setLeftRightPower(speedRight + turn, speedLeft - turn);
	}
}

void TrajectoryDriveController::setTrajectory(std::shared_ptr<Trajectory> t) {
	this->trajectory = t;
}

double TrajectoryDriveController::getGoal() {
	return 0;
}

void TrajectoryDriveController::init() {
	followerLeft->configure(0.8, 0, 0, 1.0/9.0, 1.0/40.0);
	followerRight->configure(0.8, 0, 0, 1.0/9.0, 1.0/40.0);
}

} /* namespace cougar */
