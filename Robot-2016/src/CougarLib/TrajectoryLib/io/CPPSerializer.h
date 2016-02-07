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

namespace cougar {

class CPPSerializer : public IPathSerializer {
public:
	std::string seralize(std::shared_ptr<Path> path) {

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
		 * 		std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> tmpLeft(new std::vector<std::shared_ptr<Trajectory::Segment>>);
		 *		for (int i = 0;
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

		std::string contents = "#pragma once\n";
		contents += "#include <CougarLib/TrajectoryLib/Trajectory.h>\n";
		contents += "#include <CougarLib/TrajectoryLib/Path.h>\n";
		contents += "#include <memory>\n\n";
		contents += "namespace cougar {\n\n";
		contents += "class " + path->getName() + " : public Path {\n";
		contents += "public:\n";
		path->goLeft();
		contents += "\t" + path->getName() + "() {\n";
		contents += "\t\tthis->name_ = \"" + path->getName() + "\";\n";
		contents += "\t\tthis->kLeftWheel = " + seralizeTrajectory(path->getLeftWheelTrajectory()) + ";\n";
		contents += "\t\tthis->kRightWheel = " + seralizeTrajectory(path->getRightWheelTrajectory()) + ";\n";
		contents += "\t\this->go_left_pair_ = std::shared_ptr<Trajectory::Pair>(new Trajectory::Pair(kLeftWheel, kRightWheel));\n";
		contents += "\t}\n\n";
		contents += "private:\n";
		contents += "\tstd::shared_ptr<Trajectory> kLeftWheel;\n";
		contents += "\tstd::shared_ptr<Trajectory> kRightWheel;\n";
		contents += "};\n\n";
		contents += "} // namespace cougar";

		return contents;
	}

private:
	/*
	 * std::shared_ptr<Trajectory>(new Trajectory())
	 */



	std::string seralizeTrajectory(std::shared_ptr<Trajectory> traj) {

		//std::string contents = "std::shared_ptr<Trajectory> " + name + "(new Trajectory( new std::vector<";
	}
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSERIALIZER_H_ */
