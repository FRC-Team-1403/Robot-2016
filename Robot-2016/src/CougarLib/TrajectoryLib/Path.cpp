/*
 * Path.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "Path.h"

namespace cougar {

Path::Path(std::string name, std::shared_ptr<Trajectory::Pair> go_left_pair) {
	CougarDebug::startMethod("Path::Path " + name);
	name_ = name;
	go_left_pair_ = go_left_pair;
	go_left_ = true;
	CougarDebug::endMethod("Path::Path " + this->getName());
}

Path::Path() {

}

Path::~Path() {
	CougarDebug::startMethod("Path::~Path " + this->getName());
	CougarDebug::endMethod("Path::~Path " + this->getName());
}

std::string Path::getName() {
	return name_;
}

void Path::goLeft() {
	CougarDebug::startMethod("Path::goLeft " + this->getName());
	go_left_ = true;
	go_left_pair_->left->setInvertedY(false);
	go_left_pair_->right->setInvertedY(false);
	CougarDebug::endMethod("Path::goLeft " + this->getName());
}

void Path::goRight() {
	CougarDebug::startMethod("Path::goRight " + this->getName());
	go_left_ = false;
	go_left_pair_->left->setInvertedY(true);
	go_left_pair_->right->setInvertedY(true);
	CougarDebug::endMethod("Path::goRight " + this->getName());
}

std::shared_ptr<Trajectory> Path::getLeftWheelTrajectory() {
	return (go_left_ ? go_left_pair_->left : go_left_pair_->right);
}

std::shared_ptr<Trajectory> Path::getRightWheelTrajectory() {
	return (go_left_ ? go_left_pair_->right : go_left_pair_->left);
}
std::shared_ptr<Trajectory::Pair> Path::getPair() {
	return go_left_pair_;
}

double Path::getEndHeading() {
	CougarDebug::startMethod("Path::getEndHeading " + this->getName());
	int numSegments = getLeftWheelTrajectory()->getNumSegments();
	std::shared_ptr<Trajectory::Segment> lastSegment = getLeftWheelTrajectory()->getSegment(numSegments - 1);
	CougarDebug::endMethod("Path::getEndHeading " + this->getName());
	return lastSegment->heading;
}


} /* namespace cougar */
