/*
 * CPPSerializer.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#include <CougarLib/TrajectoryLib/io/CPPSerializer.h>

namespace cougar {

std::string CPPSerializer::serialize(std::shared_ptr<Path> path)  {
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
	contents += seralizeTrajectory("kLeftWheel", path->getLeftWheelTrajectory());
	contents += seralizeTrajectory("kRightWheel", path->getRightWheelTrajectory());
	contents += "\t\this->go_left_pair_.reset(new Trajectory::Pair(kLeftWheel, kRightWheel));\n";
	contents += "\t}\n\n";
	contents += "private:\n";
	contents += "\tstd::shared_ptr<Trajectory> kLeftWheel;\n";
	contents += "\tstd::shared_ptr<Trajectory> kRightWheel;\n";
	contents += "};\n\n";
	contents += "} // namespace cougar";

	return contents;
}

std::string CPPSerializer::seralizeTrajectory(std::string name, std::shared_ptr<Trajectory> traj) {
	std::string contents = "\t\tstd::shared_ptr<std::vector<std::shared_ptr<Segment>>> tmp" + name + ";\n";
	contents == "\t\ttmp" + name + ".reset(new std::vector<std::shared_ptr<Segment>>);\n";
	for (uint32_t i = 0; i < traj->getNumSegments(); ++i) {
		std::shared_ptr<Trajectory::Segment> seg = traj->getSegment(i);
		contents += "\t\ttmp" + name + "->push_back(std::shared_ptr<Trajectory::Segment>(new Trajectory::Segment(";
		contents += seg->pos;
		contents += ", ";
		contents += seg->vel;
		contents += ", ";
		contents += seg->acc;
		contents += ", ";
		contents += seg->jerk;
		contents += ", ";
		contents += seg->heading;
		contents += ", ";
		contents += seg->dt;
		contents += ", ";
		contents += seg->x;
		contents += ", ";
		contents += seg->y;
		contents += ")));\n";
	}
	contents += "\t\tthis->" + name + ".reset(new Trajectory(tmp" + name + "));\n";
	return contents;
}

} /* namespace cougar */
