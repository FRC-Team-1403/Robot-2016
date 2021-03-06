/*
 * WaypointSequence.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 *
 * Inspired by Team 254
 * Thank you to the Cheesy Poofs for open-sourcing their code.
 *
 */

#ifndef SRC_WAYPOINTSEQUENCE_H_
#define SRC_WAYPOINTSEQUENCE_H_

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "../CougarMath.h"
#include "CougarDebug.h"

namespace cougar {

class WaypointSequence {
public:
	class Waypoint {
	public:
		Waypoint(double x, double y, double theta);
		Waypoint(std::shared_ptr<Waypoint> toCopy);

		double x;
		double y;
		double theta;
	};


	std::shared_ptr<std::vector<std::shared_ptr<Waypoint>>>waypoints_;
	uint32_t max_waypoints_;

	WaypointSequence(uint32_t max_size);
	virtual ~WaypointSequence() = default;

	virtual void addWaypoint(std::shared_ptr<Waypoint> w);
	virtual uint32_t getNumWaypoints();
	virtual std::shared_ptr<Waypoint> getWaypoint(uint32_t index);
	virtual std::shared_ptr<WaypointSequence> invertY();
};

} /* namespace cougar */

#endif /* SRC_WAYPOINTSEQUENCE_H_ */
