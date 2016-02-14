/*
 * WaypointSequence.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "WaypointSequence.h"

namespace cougar {

WaypointSequence::WaypointSequence(uint32_t max_size) {
	//CougarDebug::startMethod("WaypointSequence::WaypointSequence");
    this->waypoints_.reset(new std::vector<std::shared_ptr<Waypoint>>());
    this->max_waypoints_ = abs(max_size);
    //CougarDebug::endMethod("WaypointSequence::WaypointSequence");
}

WaypointSequence::~WaypointSequence() {
	//CougarDebug::startMethod("WaypointSequence::~WaypointSequence");
	//CougarDebug::endMethod("WaypointSequence::~WaypointSequence");
}

WaypointSequence::Waypoint::Waypoint(double x, double y, double theta) {
	//CougarDebug::startMethod("WaypointSequence::Waypoint::Waypoint");
	this->x = x;
	this->y = y;
	this->theta = theta;
	//CougarDebug::endMethod("WaypointSequence::Waypoint::Waypoint");
}

WaypointSequence::Waypoint::Waypoint(std::shared_ptr<Waypoint> toCopy) {
	//CougarDebug::startMethod("WaypointSequence::Waypoint::Waypoint");
	this->x = toCopy->x;
	this->y = toCopy->y;
	this->theta = toCopy->theta;
	//CougarDebug::endMethod("WaypointSequence::Waypoint::Waypoint");
}

void WaypointSequence::addWaypoint(std::shared_ptr<Waypoint> w) {
	//CougarDebug::startMethod("WaypointSequence::addWaypoint");
	if (this->waypoints_->size() < this->max_waypoints_) {
		this->waypoints_->push_back(w);
	} else {
		std::cout << "Index is above maximum waypoint value \n";
	}
	//CougarDebug::endMethod("WaypointSequence::addWaypoint");
}

uint32_t WaypointSequence::getNumWaypoints() {
	//CougarDebug::startMethod("WaypointSequence::getNumWaypoints");
	//CougarDebug::endMethod("WaypointSequence::getNumWaypoints");
	return this->waypoints_->size();
}

std::shared_ptr<WaypointSequence::Waypoint> WaypointSequence::getWaypoint(uint32_t index) {
	//CougarDebug::startMethod("WaypointSequence::getWaypoint");
	try {
		//CougarDebug::endMethod("WaypointSequence::getWaypoint");
		return this->waypoints_->at(index);
	} catch (const std::out_of_range& oor) {
		//CougarDebug::debugPrinter(//CougarDebug::ISSUE, "Out of range error in WaypointSequence::getWaypoint - trying to get element at index %d", index);
		std::shared_ptr<WaypointSequence::Waypoint> nullwaypnt;
		//CougarDebug::endMethod("WaypointSequence::getWaypoint");
		return nullwaypnt;
	}
}

std::shared_ptr<WaypointSequence> WaypointSequence::invertY() {
	//CougarDebug::startMethod("WaypointSequence::invertY");
	std::shared_ptr<WaypointSequence> inverted;
	inverted.reset(new WaypointSequence(this->max_waypoints_));
	for (uint32_t i = 0; i < (uint32_t)this->waypoints_->size(); ++i) {
		inverted->waypoints_->at(i) = this->waypoints_->at(i);
		inverted->waypoints_->at(i)->y *= -1;
		inverted->waypoints_->at(i)->theta =
				CougarMath::boundAngle0to2PiRadians(2*M_PI - inverted->waypoints_->at(i)->theta);
	}

	//CougarDebug::endMethod("WaypointSequence::invertY");
	return inverted;
}

} /* namespace cougar */
