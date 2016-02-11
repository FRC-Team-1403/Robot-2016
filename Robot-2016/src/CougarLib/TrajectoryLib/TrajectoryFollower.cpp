/*
 * TrajectoryFollower.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "TrajectoryFollower.h"

namespace cougar {

TrajectoryFollower::TrajectoryFollower(std::string name) {
	this->name = name;
}

void TrajectoryFollower::configure(double kp, double ki, double kd, double kv, double ka) {
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
	kv_ = kv;
	ka_ = ka;
}

void TrajectoryFollower::reset() {
	last_error_ = 0.0;
	current_segment = 0;
}

void TrajectoryFollower::setTrajectory(std::shared_ptr<Trajectory> profile) {
	profile_ = profile;
}

double TrajectoryFollower::calculate(double distance_so_far) {
	if (current_segment < profile_->getNumSegments()) {
		std::shared_ptr<Trajectory::Segment> segment = profile_->getSegment(current_segment);
		double error = segment->pos - distance_so_far;
		std::cout << "pos: " << segment->pos << "\n";
		std::cout << "distance so far: " << distance_so_far << "\n";
		std::cout << "error: " << error << "\n";
		double output = kp_ * error + kd_ * ((error - last_error_)
						/ segment->dt - segment->vel) + (kv_ * segment->vel
						+ ka_ * segment->acc);

		last_error_ = error;
		current_heading = segment->heading;
		current_segment++;
		//std::cout << "so far: " << distance_so_far << "; output: " << output << "\n";
		return output;
	} else {
		return 0;
	}
}

double TrajectoryFollower::getHeading() {
	return current_heading;
}

bool TrajectoryFollower::isFinishedTrajectory() {
	return current_segment >= profile_->getNumSegments();
}

} /* namespace cougar */
