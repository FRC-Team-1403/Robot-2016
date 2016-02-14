/*
 * Trajectory.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_TRAJECTORY_H_
#define SRC_TRAJECTORY_H_

#include "../CougarMath.h"
#include <string>
#include <vector>
#include <memory>
#include "../CougarDebug.h"

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

		virtual std::string toString();
	};

	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments_;
	bool inverted_y_ = false;

	Trajectory(uint32_t length);
	Trajectory(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments);
	virtual ~Trajectory() {

	}

	virtual void setInvertedY(bool inverted);
	virtual uint32_t getNumSegments();
	virtual std::shared_ptr<Segment> getSegment(uint32_t index);
	virtual void setSegment(uint32_t index, std::shared_ptr<Segment> segment);
	virtual void scale(double scaling_factor);
	virtual void append(std::shared_ptr<Trajectory> to_append);
	virtual std::shared_ptr<Trajectory> copy();

	virtual std::string toString();
	virtual std::string toStringProfile();
	virtual std::string toStringEuclidean();

private:
	virtual std::shared_ptr<std::vector<std::shared_ptr<Segment>>> copySegments(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> tocopy);
};

} /* namespace cougar */

#endif /* SRC_TRAJECTORY_H_ */
