/*
 * CPPSerializer.h
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSERIALIZER_H_

#include "IPathSerializer.h"
#include "../Path.h"
#include <memory>
#include <string>

namespace cougar {

class CPPSerializer : public IPathSerializer {
public:

	/*
	 * #pragma once
	 * #include <CougarLib/TrajectoryLib/Trajectory.h>
	 * #include <CougarLib/TrajectoryLib/Path.h>
	 * #include <memory>
	 *
	 * namespace cougar {
	 * class path->getName() : public Path {
	 * public:
	 * 	path->getName() {
	 * 		this->name = "path->getName()";
	 * 		vector <segment*>* v = new vector<segment*>;
	 * 		v->push_back(new Segment(1, 2, 3);
	 * 		this->kLeftWheel = new Trajectory(v);
	 * 		this->kLeftWheel = seralizeTrajectory(path->getLeftWheelTrajectory());
	 *		this->kRightWheel = seralizeTrajectory(path->getRightWheelTrajectory());
	 *		this->go_left_pair_ = std::shared_ptr<Trajectory::Pair>(new Trajectory::Pair(kLeftWheel, kRightWheel));
	 *	}
	 * private:
	 * 	std::shared_ptr<Trajectory> kLeftWheel;
	 * 	std::shared_ptr<Trajectory> kRightWheel;
	 * };
	 *
	 * } // namespace cougar
	 *
	 */
	virtual std::string serialize(std::shared_ptr<Path> path) override;

private:

	/*
	 * std::shared_ptr<std::vector<std::shared_ptr<Segment>>> tmpname;
	 * tmpname.reset(new std::vector<std::shared_ptr<Segment>>);
	 * tmpname->push_back(std::shared_ptr<Trajectory::Segment>(new Trajectory::Segment(pos, vel, acc, jerk, heading, dt, x, y)));
	 * ...
	 * this->name.reset(new Trajectory(tmpname));
	 */
	virtual std::string seralizeTrajectory(std::string name, std::shared_ptr<Trajectory> traj);
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSERIALIZER_H_ */
