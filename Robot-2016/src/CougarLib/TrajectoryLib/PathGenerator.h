/*
 * PathGenerator.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_PATHGENERATOR_H_
#define SRC_PATHGENERATOR_H_

#include "WPILib.h"
#include "Trajectory.h"
#include "TrajectoryGenerator.h"
#include "Spline.h"
#include "WaypointSequence.h"
#include "Path.h"
#include <cmath>

namespace cougar {


class PathGenerator {
public:
	/**
	 * Generate a path for autonomous driving.
	 *
	 * @param waypoints The waypoints to drive to (FOR THE "GO LEFT" CASE!!!!)
	 * @param config Trajectory config.
	 * @param wheelbase_width Wheelbase separation; units must be consistent with
	 * config and waypoints.
	 * @param name The name of the new path.	THIS MUST BE A VALID JAVA CLASS NAME
	 * @return The path.
	 */
	static std::shared_ptr<Path> makePath(std::shared_ptr<WaypointSequence> waypoints,
			std::shared_ptr<TrajectoryGenerator::Config> config, double wheelbase_width,
					std::string name);
private:
	static std::shared_ptr<Trajectory::Pair> generateLeftAndRightFromSeq(std::shared_ptr<WaypointSequence> path,
			std::shared_ptr<TrajectoryGenerator::Config> config, double wheelbase_width);

	static std::shared_ptr<Trajectory> generateFromPath(std::shared_ptr<WaypointSequence> path,
			std::shared_ptr<TrajectoryGenerator::Config> config);

	/**
	 * Generate left and right wheel trajectories from a reference.
	 *
	 * @param input The reference trajectory.
	 * @param wheelbase_width The center-to-center distance between the left and
	 * right sides.
	 * @return [0] is left, [1] is right
	 */
	static std::shared_ptr<Trajectory::Pair> makeLeftAndRightTrajectories(std::shared_ptr<Trajectory> input,
					double wheelbase_width);
};

} /* namespace cougar */

#endif /* SRC_PATHGENERATOR_H_ */
