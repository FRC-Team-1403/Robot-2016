/*
 * TrajectoryDriveController.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_

#include "../CougarController.h"
#include "Trajectory.h"
#include "TrajectoryFollower.h"
#include "../CougarMath.h"
#include <memory>

namespace cougar {

class TrajectoryDriveController : public CougarController {
public:
	explicit TrajectoryDriveController();

	virtual ~TrajectoryDriveController() {

	}

	std::shared_ptr<Trajectory> trajectory;
	std::shared_ptr<TrajectoryFollower> followerLeft;
	std::shared_ptr<TrajectoryFollower> followerRight;
	double direction;
	double heading;
	double kTurn = -3.0/80.0;

	bool onTarget() {
		return followerLeft->isFinishedTrajectory();
	}



	virtual void loadProfile(std::shared_ptr<Trajectory> leftProfile, std::shared_ptr<Trajectory> rightProfile, double direction, double heading) {
		reset();
		followerLeft->setTrajectory(leftProfile);
		followerRight->setTrajectory(rightProfile);
		this->direction = direction;
		this->heading = heading;
	}

	virtual void loadProfileNoReset(std::shared_ptr<Trajectory> leftProfile, std::shared_ptr<Trajectory> rightProfile) {
		followerLeft->setTrajectory(leftProfile);
		followerRight->setTrajectory(rightProfile);
	}

	virtual void reset();

	virtual int getFollowerCurrentSegment() {
		return followerLeft->getCurrentSegment();
	}

	virtual int getNumSegments() {
		return followerLeft->getNumSegments();
	}

	virtual void update();

	void setTrajectory(std::shared_ptr<Trajectory> t) {
		this->trajectory = t;
	}

	double getGoal() {
		return 0;
	}

private:
	void init() {
		followerLeft->configure(1.5, 0, 0, 1.0/15.0, 1.0/34.0);
		followerRight->configure(1.5, 0, 0, 1.0/15.0, 1.0/34.0);
	}

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_ */
