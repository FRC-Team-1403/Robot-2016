/*
 * Path.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include "Trajectory.h"

namespace cougar {

class Path {
public:

	Path(std::string name, std::shared_ptr<Trajectory::Pair> go_left_pair);
	Path();
	virtual ~Path();

	virtual std::string getName();
	virtual void goLeft();
	virtual void goRight();
	virtual std::shared_ptr<Trajectory> getLeftWheelTrajectory();
	virtual std::shared_ptr<Trajectory> getRightWheelTrajectory();
	virtual std::shared_ptr<Trajectory::Pair> getPair();
	virtual double getEndHeading();

protected:
	std::shared_ptr<Trajectory::Pair> go_left_pair_;
	std::string name_;
	bool go_left_;

};

} /* namespace cougar */

#endif /* SRC_PATH_H_ */
