/*
 * WaypointSequence.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "WaypointSequence.h"

namespace cougar {

WaypointSequence::WaypointSequence(uint32_t max_size) {
    this->waypoints_.reset(new std::vector<std::shared_ptr<Waypoint>>());
    this->max_waypoints_ = abs(max_size);
}

WaypointSequence::Waypoint::Waypoint(double x, double y, double theta) {
	this->x = x;
	this->y = y;
	this->theta = theta;
}

WaypointSequence::Waypoint::Waypoint(std::shared_ptr<Waypoint> toCopy) {
	this->x = toCopy->x;
	this->y = toCopy->y;
	this->theta = toCopy->theta;
}

void WaypointSequence::addWaypoint(std::shared_ptr<Waypoint> w) {
	if (this->waypoints_->size() < this->max_waypoints_) {
		this->waypoints_->push_back(w);
	} else {
		CougarDebug::debugPrinter(CougarDebug::FATAL_ERROR, "Index is above maximum waypoint value");
	}
}

uint32_t WaypointSequence::getNumWaypoints() {
	return this->waypoints_->size();
}

std::shared_ptr<WaypointSequence::Waypoint> WaypointSequence::getWaypoint(uint32_t index) {
	try {
		return this->waypoints_->at(index);
	} catch (const std::out_of_range& oor) {
		return std::shared_ptr<WaypointSequence::Waypoint>(new WaypointSequence::Waypoint(0, 0, 0));
	}
}

std::shared_ptr<WaypointSequence> WaypointSequence::invertY() {
	std::shared_ptr<WaypointSequence> inverted;
	inverted.reset(new WaypointSequence(this->max_waypoints_));
	for (uint32_t i = 0; i < (uint32_t)this->waypoints_->size(); ++i) {
		inverted->waypoints_->at(i) = this->waypoints_->at(i);
		inverted->waypoints_->at(i)->y *= -1;
		inverted->waypoints_->at(i)->theta =
				CougarMath::boundAngle0to2PiRadians(2*M_PI - inverted->waypoints_->at(i)->theta);
	}

	return inverted;
}

} /* namespace cougar */
