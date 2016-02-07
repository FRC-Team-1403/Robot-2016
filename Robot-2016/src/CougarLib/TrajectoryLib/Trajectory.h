/*
 * Trajectory.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_TRAJECTORY_H_
#define SRC_TRAJECTORY_H_

#include "WPILib.h"
#include "../CougarMath.h"
#include <string>
#include <memory>

namespace cougar {

class Trajectory {
public:
	class Pair {
	public:
		Pair(std::shared_ptr<Trajectory> left, std::shared_ptr<Trajectory> right);

		std::shared_ptr<Trajectory> left;
		std::shared_ptr<Trajectory> right;
	};

	class Segment {
	public:
		double pos, vel, acc, jerk, heading, dt, x, y;

		Segment();
		Segment(double pos, double vel, double acc, double jerk,
						double heading, double dt, double x, double y);
		Segment(std::shared_ptr<Segment> to_copy);

		std::string toString();
	};

	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments_;
	bool inverted_y_ = false;

	Trajectory(uint32_t length);
	Trajectory(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments);

	void setInvertedY(bool inverted);
	uint32_t getNumSegments();
	std::shared_ptr<Segment> getSegment(uint32_t index);
	void setSegment(uint32_t index, std::shared_ptr<Segment> segment);
	void scale(double scaling_factor);
	void append(std::shared_ptr<Trajectory> to_append);
	std::shared_ptr<Trajectory> copy();

	std::string toString();
	std::string toStringProfile();
	std::string toStringEuclidean();

private:
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> copySegments(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> tocopy);
};

} /* namespace cougar */

#endif /* SRC_TRAJECTORY_H_ */
