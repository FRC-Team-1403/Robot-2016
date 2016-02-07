/*
 * TrajectoryFollower.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_TRAJECTORYFOLLOWER_H_
#define SRC_TRAJECTORYFOLLOWER_H_

#include "WPILib.h"
#include "Trajectory.h"

namespace cougar {

class TrajectoryFollower {
public:
	TrajectoryFollower();

	void configure(double kp, double ki, double kd, double kv, double ka);
	void reset();
	void setTrajectory(std::shared_ptr<Trajectory> profile);
	double calculate(double distance_so_far);
	double getHeading();
	bool isFinishedTrajectory();

private:
	double kp_;
	double ki_;	// Not currently used, but might be in the future.
	double kd_;
	double kv_;
	double ka_;
	double last_error_;
	double current_heading = 0;
	uint32_t current_segment;
	std::shared_ptr<Trajectory> profile_;

};

} /* namespace cougar */

#endif /* SRC_TRAJECTORYFOLLOWER_H_ */
