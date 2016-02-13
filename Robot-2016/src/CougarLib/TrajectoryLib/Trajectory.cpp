/*
 * Trajectory.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "Trajectory.h"

namespace cougar {

Trajectory::Pair::Pair(std::shared_ptr<Trajectory> left, std::shared_ptr<Trajectory> right) {
	CougarDebug::startMethod("Trajectory::Pair::Pair");
	this->left = left;
	this->right = right;
	CougarDebug::endMethod("Trajectory::Pair::Pair");
}

Trajectory::Segment::Segment() {
	CougarDebug::startMethod("Trajectory::Segment::Segment");
	CougarDebug::endMethod("Trajectory::Segment::Segment");
}

Trajectory::Segment::Segment(double pos, double vel, double acc, double jerk,
						double heading, double dt, double x, double y) {
	CougarDebug::startMethod("Trajectory::Segment::Segment");
	this->pos = pos;
	this->vel = vel;
	this->acc = acc;
	this->jerk = jerk;
	this->heading = heading;
	this->dt = dt;
	this->x = x;
	this->y = y;
	CougarDebug::endMethod("Trajectory::Segment::Segment");
}

Trajectory::Segment::Segment(std::shared_ptr<Segment> to_copy) {
	CougarDebug::startMethod("Trajectory::Segment::Segment");
	pos = to_copy->pos;
	vel = to_copy->vel;
	acc = to_copy->acc;
	jerk = to_copy->jerk;
	heading = to_copy->heading;
	dt = to_copy->dt;
	x = to_copy->x;
	y = to_copy->y;
	CougarDebug::endMethod("Trajectory::Segment::Segment");
}

std::string Trajectory::Segment::toString() {
	CougarDebug::startMethod("Trajectory::Segment::toString");
	CougarDebug::endMethod("Trajectory::Segment::toString");
	return std::string("pos: ") + std::to_string(pos) + "; vel: " + std::to_string(vel) + "; acc: " + std::to_string(acc) + "; jerk: "
					+ std::to_string(jerk) + "; heading: " + std::to_string(heading);
	return "";
}

Trajectory::Trajectory(uint32_t length) {
	CougarDebug::startMethod("Trajectory::Trajectory");
	segments_.reset(new std::vector<std::shared_ptr<Segment>>());
	CougarDebug::endMethod("Trajectory::Trajectory");
	for (uint32_t i = 0; i < length; ++i) {
		segments_->push_back(std::shared_ptr<Segment>(new Segment()));
	}
}

Trajectory::Trajectory(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments) {
	CougarDebug::startMethod("Trajectory::Trajectory");
	segments_ = segments;
	CougarDebug::endMethod("Trajectory::Trajectory");
}

void Trajectory::setInvertedY(bool inverted) {
	CougarDebug::startMethod("Trajectory::setInvertedY");
	inverted_y_ = inverted;
	CougarDebug::endMethod("Trajectory::setInvertedY");
}

uint32_t Trajectory::getNumSegments() {
	CougarDebug::startMethod("Trajectory::getNumSegments");
	CougarDebug::endMethod("Trajectory::getNumSegments");
	return segments_->size();
}

std::shared_ptr<Trajectory::Segment> Trajectory::getSegment(uint32_t index) {
	CougarDebug::startMethod("Trajectory::getSegment");
	if (index < getNumSegments()) {
		if (!inverted_y_) {
			CougarDebug::endMethod("Trajectory::getSegment");
			return segments_->at(index);
		} else {
			std::shared_ptr<Segment> segment(new Segment(segments_->at(index)));
			segment->y *= -1.0;
			segment->heading *= -1.0;
			CougarDebug::endMethod("Trajectory::getSegment");
			return segment;
		}
	} else {
		CougarDebug::endMethod("Trajectory::getSegment");
		return std::shared_ptr<Segment>(new Segment());
	}
}

void Trajectory::setSegment(uint32_t index, std::shared_ptr<Segment> segment) {
	CougarDebug::startMethod("Trajectory::setSegment");
	if (index < getNumSegments()) {
		segments_->at(index) = segment;
	}
	CougarDebug::endMethod("Trajectory::setSegment");
}

void Trajectory::scale(double scaling_factor) {
	CougarDebug::startMethod("Trajectory::scale");
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		segments_->at(i)->pos *= scaling_factor;
		segments_->at(i)->vel *= scaling_factor;
		segments_->at(i)->acc *= scaling_factor;
		segments_->at(i)->jerk *= scaling_factor;
	}
	CougarDebug::endMethod("Trajectory::scale");
}

void Trajectory::append(std::shared_ptr<Trajectory> to_append) {
	CougarDebug::startMethod("Trajectory::append");
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> temp(new std::vector<std::shared_ptr<Segment>>());

	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		temp->push_back(std::shared_ptr<Segment>(new Segment(segments_->at(i))));
	}
	for (uint32_t i = 0; i < to_append->getNumSegments(); ++i) {
		temp->push_back(std::shared_ptr<Segment>(new Segment(to_append->getSegment(i))));
	}

	this->segments_ = temp;
	CougarDebug::endMethod("Trajectory::append");
}

std::shared_ptr<Trajectory> Trajectory::copy() {
	CougarDebug::startMethod("Trajectory::copy");
	std::shared_ptr<Trajectory> cloned(new Trajectory(getNumSegments()));
	cloned->segments_ = copySegments(this->segments_);
	CougarDebug::endMethod("Trajectory::copy");
	return cloned;
}

std::string Trajectory::toString() {
	CougarDebug::startMethod("Trajectory::toString");
	std::string str = "Segment\tPos\tVel\tAcc\tJerk\tHeading\n";
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		Trajectory::Segment segment = getSegment(i);
		str += std::to_string(i) + "\t";
		str += std::to_string(segment.pos) + "\t";
		str += std::to_string(segment.vel) + "\t";
		str += std::to_string(segment.acc) + "\t";
		str += std::to_string(segment.jerk) + "\t";
		str += std::to_string(segment.heading) + "\t";
		str += "\n";
	}
	CougarDebug::endMethod("Trajectory::toString");
	return str;
}

std::string Trajectory::toStringProfile() {
	CougarDebug::startMethod("Trajectory::toStringProfile");
	CougarDebug::endMethod("Trajectory::toStringProfile");
	return toString();
}

std::string Trajectory::toStringEuclidean() {
	CougarDebug::startMethod("Trajectory::toStringEuclidean");
	/*
	std::string str = "Segment\tx\ty\tHeading\n";
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		Trajectory::Segment segment = getSegment(i);
		str += i + "\t";
		str += segment.x + "\t";
		str += segment.y + "\t";
		str += segment.heading + "\t";
		str += "\n";
	}

	return str;
	*/

	CougarDebug::endMethod("Trajectory::toStringEuclidean");
	return "";
}

std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> Trajectory::copySegments(std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> tocopy) {
	CougarDebug::startMethod("Trajectory::copySegments");
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> copied(new std::vector<std::shared_ptr<Segment>>());
	for (uint32_t i = 0; i < tocopy->size(); ++i) {
		copied->push_back(std::shared_ptr<Segment>(new Segment(tocopy->at(i))));
	}
	CougarDebug::endMethod("Trajectory::copySegments");
	return copied;
}

} /* namespace cougar */
