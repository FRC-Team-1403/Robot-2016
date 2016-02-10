/*
 * PathGenerator.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "PathGenerator.h"

namespace cougar {

std::shared_ptr<Path> PathGenerator::makePath(std::shared_ptr<WaypointSequence> waypoints,
		std::shared_ptr<TrajectoryGenerator::Config> config, double wheelbase_width,
				std::string name) {
	cougar::CougarDebug::debugPrinter("PathGenerator::makePath started");
	return std::shared_ptr<Path>(new Path(name,
					generateLeftAndRightFromSeq(waypoints, config, wheelbase_width)));
	cougar::CougarDebug::debugPrinter("PathGenerator::makePath finished");
}

std::shared_ptr<Trajectory::Pair> PathGenerator::generateLeftAndRightFromSeq(std::shared_ptr<WaypointSequence> path,
		std::shared_ptr<TrajectoryGenerator::Config> config, double wheelbase_width) {
	cougar::CougarDebug::debugPrinter("PathGenerator::generateLeftAndRightFromSeq started");
	return makeLeftAndRightTrajectories(generateFromPath(path, config),
					wheelbase_width);
	cougar::CougarDebug::debugPrinter("PathGenerator::generateLeftAndRightFromSeq finished");
}

std::shared_ptr<Trajectory> PathGenerator::generateFromPath(std::shared_ptr<WaypointSequence> path,
		std::shared_ptr<TrajectoryGenerator::Config> config) {
	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath started");
	if (path->getNumWaypoints() < 2) {
		//TODO fix
		//return nullptr;
		std::shared_ptr<Trajectory> tmp;
		return tmp;
	}

	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.1");

	// Compute the total length of the path by creating splines for each pair
	// of waypoints.
	std::shared_ptr<std::vector<std::shared_ptr<Spline>>> splines;
	splines.reset(new std::vector<std::shared_ptr<Spline>>);
	std::shared_ptr<std::vector<double>> spline_lengths; // Remember, Mrs. Jessu said not to use parallel lists!
	spline_lengths.reset(new std::vector<double>);
	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.2");
	double total_distance = 0;
	for (uint32_t i = 0; i < path->getNumWaypoints() - 1; ++i) {
		cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.3.1");
		splines->push_back(std::shared_ptr<Spline>(new Spline()));
		cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.3.1.1");
		//splines[i] = new Spline();
		try {
			splines->at(i);
		} catch (const std::out_of_range& oor) {
			CougarDebug::debugPrinter(CougarDebug::ISSUE, "Out of range error in PathGenerator::generateFromPath; trying to get element at index %d", i);
		}
		if (!Spline::reticulateSplines(path->getWaypoint(i),
						path->getWaypoint(i + 1), splines->at(i), Spline::QuinticHermite)) {
			// TODO fix
			//return nullptr;
			std::shared_ptr<Trajectory> tmp;
			cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.3.2");
			return tmp;
		}
		cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.3.3.1");
		spline_lengths->push_back(splines->at(i)->calculateLength());
		total_distance += spline_lengths->at(i);
		cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1.3.3.2");
	}
	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 1");

	// Generate a smooth trajectory over the total distance.
	std::shared_ptr<Trajectory> traj = TrajectoryGenerator::generate(config,
					TrajectoryGenerator::SCurvesStrategy, 0.0, path->getWaypoint(0)->theta,
					total_distance, 0.0, path->getWaypoint(0)->theta);

	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath checkpoint 2");


	// Assign headings based on the splines.
	uint32_t cur_spline = 0;
	double cur_spline_start_pos = 0;
	double length_of_splines_finished = 0;
	for (uint32_t i = 0; i < traj->getNumSegments(); ++i) {
		double cur_pos = traj->getSegment(i)->pos;

		bool found_spline = false;
		while (!found_spline) {
			double cur_pos_relative = cur_pos - cur_spline_start_pos;
			if (cur_pos_relative <= spline_lengths->at(cur_spline)) {
				double percentage = splines->at(cur_spline)->getPercentageForDistance(
								cur_pos_relative);
				traj->getSegment(i)->heading = splines->at(cur_spline)->angleAt(percentage);
				std::shared_ptr<std::vector<double>> coords = splines->at(cur_spline)->getXandY(percentage);
				traj->getSegment(i)->x = coords->at(0);
				traj->getSegment(i)->y = coords->at(1);
				found_spline = true;
			} else if (cur_spline < splines->size() - 1) {
				length_of_splines_finished += spline_lengths->at(cur_spline);
				cur_spline_start_pos = length_of_splines_finished;
				++cur_spline;
			} else {
				traj->getSegment(i)->heading = splines->at(splines->size() - 1)->angleAt(1.0);
				std::shared_ptr<std::vector<double>>  coords = splines->at(splines->size() - 1)->getXandY(1.0);
				traj->getSegment(i)->x = coords->at(0);
				traj->getSegment(i)->y = coords->at(1);
				found_spline = true;
			}
		}
	}
	cougar::CougarDebug::debugPrinter("PathGenerator::generateFromPath finished");
	return traj;

}

std::shared_ptr<Trajectory::Pair> PathGenerator::makeLeftAndRightTrajectories(std::shared_ptr<Trajectory> input,
				double wheelbase_width) {
	cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories started");
	std::shared_ptr<std::vector<std::shared_ptr<Trajectory>>> output;// = new Trajectory[2];
	output.reset(new std::vector<std::shared_ptr<Trajectory>>);
	output->push_back(0);
	output->push_back(0);
	output->at(0) = input->copy();
	output->at(1) = input->copy();
	std::shared_ptr<Trajectory> left = output->at(0);
	std::shared_ptr<Trajectory> right = output->at(1);
	cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories checkpoint 1");


	for (uint32_t i = 0; i < input->getNumSegments(); ++i) {
		cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories checkpoint 2.1");
		std::shared_ptr<Trajectory::Segment> current = input->getSegment(i);
		double cos_angle = cos(current->heading);
		double sin_angle = sin(current->heading);

		std::shared_ptr<Trajectory::Segment> s_left = left->getSegment(i);
		s_left->x = current->x - wheelbase_width / 2 * sin_angle;
		s_left->y = current->y + wheelbase_width / 2 * cos_angle;
		if (i > 0) {
			// Get distance between current and last segment
			double dist = sqrt((s_left->x - left->getSegment(i - 1)->x)
							* (s_left->x - left->getSegment(i - 1)->x)
							+ (s_left->y - left->getSegment(i - 1)->y)
							* (s_left->y - left->getSegment(i - 1)->y));
			s_left->pos = left->getSegment(i - 1)->pos + dist;
			s_left->vel = dist / s_left->dt;
			s_left->acc = (s_left->vel - left->getSegment(i - 1)->vel) / s_left->dt;
			s_left->jerk = (s_left->acc - left->getSegment(i - 1)->acc) / s_left->dt;
		}
		cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories checkpoint 2.2");

		std::shared_ptr<Trajectory::Segment> s_right = right->getSegment(i);
		s_right->x = current->x + wheelbase_width / 2 * sin_angle;
		s_right->y = current->y - wheelbase_width / 2 * cos_angle;
		if (i > 0) {
			// Get distance between current and last segment
			double dist = sqrt((s_right->x - right->getSegment(i - 1)->x)
							* (s_right->x - right->getSegment(i - 1)->x)
							+ (s_right->y - right->getSegment(i - 1)->y)
							* (s_right->y - right->getSegment(i - 1)->y));
			s_right->pos = right->getSegment(i - 1)->pos + dist;
			s_right->vel = dist / s_right->dt;
			s_right->acc = (s_right->vel - right->getSegment(i - 1)->vel) / s_right->dt;
			s_right->jerk = (s_right->acc - right->getSegment(i - 1)->acc) / s_right->dt;
		}
		cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories checkpoint 2.3");
	}
	cougar::CougarDebug::debugPrinter("PathGenerator::makeLeftAndRightTrajectories finished");
	return std::shared_ptr<Trajectory::Pair>(new Trajectory::Pair(output->at(0), output->at(1)));
}

} /* namespace cougar */
