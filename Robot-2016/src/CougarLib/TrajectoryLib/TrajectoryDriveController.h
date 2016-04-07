/*
 * TrajectoryDriveController.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 *
 * Inspired by Team 254
 * Thank you to the Cheesy Poofs for open-sourcing their code.
 *
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_

#include "../CougarController.h"
#include "Trajectory.h"
#include "TrajectoryFollower.h"
#include "../CougarMath.h"
#include <memory>
#include <iostream>

namespace cougar {

class TrajectoryDriveController : public CougarController {
public:
	explicit TrajectoryDriveController();

	virtual ~TrajectoryDriveController() {}

	std::shared_ptr<Trajectory> trajectory;
	std::shared_ptr<TrajectoryFollower> followerLeft;
	std::shared_ptr<TrajectoryFollower> followerRight;
	double direction;
	double heading;
	double kTurn = -11.0/80.0;

	virtual bool onTarget();
	virtual void loadProfile(std::shared_ptr<Trajectory> leftProfile,
			std::shared_ptr<Trajectory> rightProfile, double direction, double heading);
	virtual void loadProfileNoReset(std::shared_ptr<Trajectory> leftProfile,
			std::shared_ptr<Trajectory> rightProfile);
	virtual void reset() override;
	virtual int getFollowerCurrentSegment();
	virtual int getNumSegments();
	virtual void update() override;
	virtual void setTrajectory(std::shared_ptr<Trajectory> t);
	virtual double getGoal() override;

private:
	virtual void init();

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_TRAJECTORYDRIVECONTROLLER_H_ */
