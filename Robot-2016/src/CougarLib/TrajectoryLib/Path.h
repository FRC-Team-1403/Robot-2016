/*
 * Path.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include "WPILib.h"
#include "Trajectory.h"

namespace cougar {

class Path {
public:

	Path(std::string name, std::shared_ptr<Trajectory::Pair> go_left_pair) {
		name_ = name;
		go_left_pair_ = go_left_pair;
		go_left_ = true;
	}

	Path() {

	}

	std::string getName() { return name_; }

	void goLeft() {
		go_left_ = true;
		go_left_pair_->left->setInvertedY(false);
		go_left_pair_->right->setInvertedY(false);
	}

	void goRight() {
		go_left_ = false;
		go_left_pair_->left->setInvertedY(true);
		go_left_pair_->right->setInvertedY(true);
	}

	std::shared_ptr<Trajectory> getLeftWheelTrajectory() {
		return (go_left_ ? go_left_pair_->left : go_left_pair_->right);
	}

	std::shared_ptr<Trajectory> getRightWheelTrajectory() {
		return (go_left_ ? go_left_pair_->right : go_left_pair_->left);
	}

	std::shared_ptr<Trajectory::Pair> getPair() {
		return go_left_pair_;
	}

	double getEndHeading() {
		int numSegments = getLeftWheelTrajectory()->getNumSegments();
		std::shared_ptr<Trajectory::Segment> lastSegment = getLeftWheelTrajectory()->getSegment(numSegments - 1);
		return lastSegment->heading;
	}

protected:
	std::shared_ptr<Trajectory::Pair> go_left_pair_;
	std::string name_;
	bool go_left_;

};

} /* namespace cougar */

#endif /* SRC_PATH_H_ */
