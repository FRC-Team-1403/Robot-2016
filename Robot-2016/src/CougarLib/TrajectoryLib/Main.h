/*
 * Main.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "io/CPPSerializer.h"
#include "io/CPPStringSerializer.h"
#include "io/TextFileSerializer.h"
#include "TrajectoryGenerator.h"
#include "WaypointSequence.h"
#include "PathGenerator.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <cmath>

namespace cougar {

class Main {
public:
	static std::string joinPath(std::string directory, std::string name) {
		return directory + name;
	}

	static bool writeFile(std::string path, std::string data) {
		std::ofstream file(path);
		file << data;
		return true;
	}

	static int execute() {
		std::string directory = "../FRC-2016/paths";

		std::shared_ptr<TrajectoryGenerator::Config> config(new TrajectoryGenerator::Config());
		//TODO find these values
		const double kWheelbaseWidth = 25.5/12;
		config->dt = 0.01;
		config->max_acc = 100;
		config->max_jerk = 100;
		config->max_vel = 100;

		const std::string path_name = "TEST";

		std::shared_ptr<WaypointSequence> p(new WaypointSequence(10));
		p->addWaypoint(std::shared_ptr<WaypointSequence::Waypoint>(new WaypointSequence::Waypoint(0, 0, 0)));
		p->addWaypoint(std::shared_ptr<WaypointSequence::Waypoint>(new WaypointSequence::Waypoint(7.0, 0, 0)));
		p->addWaypoint(std::shared_ptr<WaypointSequence::Waypoint>(new WaypointSequence::Waypoint(14.0, 1.0, M_PI / 12.0)));

		std::shared_ptr<Path> path = PathGenerator::makePath(p, config,
				kWheelbaseWidth, path_name);

		// Outputs to the directory supplied as the first argument.
		std::shared_ptr<TextFileSerializer> js(new TextFileSerializer());
		std::string serialized = js->serialize(path);
		//System.out.print(serialized);
		std::string fullpath = joinPath(directory, path_name + ".txt");
		if (!writeFile(fullpath, serialized)) {
			std::cout << fullpath << " could not be written!!!!\n";
			return 1;
		} else {
			std::cout << "Wrote " << fullpath;
			return 0;
		}
	}
};

} /* namespace cougar */

#endif /* SRC_MAIN_H_ */
