/*
 * Trajectory.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "Trajectory.h"

namespace cougar {

Trajectory::Pair::Pair(std::shared_ptr<Trajectory> left, std::shared_ptr<Trajectory> right) {
	this->left = left;
	this->right = right;
}

Trajectory::Segment::Segment() {

}

Trajectory::Segment::Segment(double pos, double vel, double acc, double jerk,
						double heading, double dt, double x, double y) {
	this->pos = pos;
	this->vel = vel;
	this->acc = acc;
	this->jerk = jerk;
	this->heading = heading;
	this->dt = dt;
	this->x = x;
	this->y = y;
}

Trajectory::Segment::Segment(std::shared_ptr<Segment> to_copy) {
	pos = to_copy->pos;
	vel = to_copy->vel;
	acc = to_copy->acc;
	jerk = to_copy->jerk;
	heading = to_copy->heading;
	dt = to_copy->dt;
	x = to_copy->x;
	y = to_copy->y;
}

std::string Trajectory::Segment::toString() {
	return std::string("pos: ") + std::to_string(pos) + "; vel: " + std::to_string(vel) + "; acc: " + std::to_string(acc) + "; jerk: "
					+ std::to_string(jerk) + "; heading: " + std::to_string(heading);
}

Trajectory::Trajectory(uint32_t length) {
	segments_.reset(new std::vector<std::shared_ptr<Segment>>());
	for (uint32_t i = 0; i < length; ++i) {
		segments_->push_back(std::shared_ptr<Segment>(new Segment()));
	}
}

Trajectory::Trajectory(std::shared_ptr<std::vector<std::shared_ptr<Segment>>> segments) {
	segments_ = segments;
}

void Trajectory::setInvertedY(bool inverted) {
	CougarDebug::startMethod("Trajectory::setInvertedY");
	inverted_y_ = inverted;
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "Trajectory::inverted_y_ set to %d", inverted);
	CougarDebug::endMethod("Trajectory::setInvertedY");
}

uint32_t Trajectory::getNumSegments() {
	return segments_->size();
}

std::shared_ptr<Trajectory::Segment> Trajectory::getSegment(uint32_t index) {
	if (index < getNumSegments()) {
		if (!inverted_y_) {
			return segments_->at(index);
		} else {
			std::shared_ptr<Segment> segment(new Segment(segments_->at(index)));
			segment->y *= -1.0;
			segment->heading *= -1.0;
			return segment;
		}
	} else {
		return std::shared_ptr<Segment>(new Segment());
	}
}

void Trajectory::setSegment(uint32_t index, std::shared_ptr<Segment> segment) {
	if (index < getNumSegments()) {
		segments_->at(index) = segment;
	}
}

void Trajectory::scale(double scaling_factor) {
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		segments_->at(i)->pos *= scaling_factor;
		segments_->at(i)->vel *= scaling_factor;
		segments_->at(i)->acc *= scaling_factor;
		segments_->at(i)->jerk *= scaling_factor;
	}
}

void Trajectory::append(std::shared_ptr<Trajectory> to_append) {
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> temp(new std::vector<std::shared_ptr<Segment>>());

	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		temp->push_back(std::shared_ptr<Segment>(new Segment(segments_->at(i))));
	}
	for (uint32_t i = 0; i < to_append->getNumSegments(); ++i) {
		temp->push_back(std::shared_ptr<Segment>(new Segment(to_append->getSegment(i))));
	}

	this->segments_ = temp;
}

std::shared_ptr<Trajectory> Trajectory::copy() {
	std::shared_ptr<Trajectory> cloned(new Trajectory(getNumSegments()));
	cloned->segments_ = copySegments(this->segments_);
	return cloned;
}

std::string Trajectory::toString() {
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
	return str;
}

std::string Trajectory::toStringProfile() {
	return toString();
}

std::string Trajectory::toStringEuclidean() {
	std::string str = "Segment\tx\ty\tHeading\n";
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		Trajectory::Segment segment = getSegment(i);
		str += std::to_string(i) + "\t";
		str += std::to_string(segment.x) + "\t";
		str += std::to_string(segment.y) + "\t";
		str += std::to_string(segment.heading) + "\t";
		str += "\n";
	}

	return str;
}

std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> Trajectory::copySegments(std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> tocopy) {
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> copied(new std::vector<std::shared_ptr<Segment>>());
	for (uint32_t i = 0; i < tocopy->size(); ++i) {
		copied->push_back(std::shared_ptr<Segment>(new Segment(tocopy->at(i))));
	}
	return copied;
}

} /* namespace cougar */
