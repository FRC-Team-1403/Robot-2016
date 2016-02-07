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

Trajectory::Segment::Segment() {}

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
	//return std::string("pos: " + std::to_string(pos).c_str() + "; vel: " + std::to_string(vel).c_str() + "; acc: " + std::to_string(acc).c_str() + "; jerk: "
	//				+ std::to_string(jerk).c_str() + "; heading: " + std::to_string(heading).c_str());
	return "";
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
	inverted_y_ = inverted;
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
	/*
	std::string str = "Segment\tPos\tVel\tAcc\tJerk\tHeading\n";
	for (uint32_t i = 0; i < getNumSegments(); ++i) {
		Trajectory::Segment segment = getSegment(i);
		str += i + "\t";
		str += segment.pos + "\t";
		str += segment.vel + "\t";
		str += segment.acc + "\t";
		str += segment.jerk + "\t";
		str += segment.heading + "\t";
		str += "\n";
	}

	return str;
	*/
	return "";
}

std::string Trajectory::toStringProfile() {
	return toString();
}

std::string Trajectory::toStringEuclidean() {
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
	return "";
}

std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> Trajectory::copySegments(std::shared_ptr<std::vector<std::shared_ptr<Trajectory::Segment>>> tocopy) {
	std::shared_ptr<std::vector<std::shared_ptr<Segment>>> copied(new std::vector<std::shared_ptr<Segment>>());
	for (uint32_t i = 0; i < tocopy->size(); ++i) {
		copied->push_back(std::shared_ptr<Segment>(new Segment(tocopy->at(i))));
	}
	return copied;
}

} /* namespace cougar */
