/*
 * Spline.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_SPLINE_H_
#define SRC_SPLINE_H_

#include <cmath>
#include "WPILib.h"
#include "../CougarMath.h"
#include "WaypointSequence.h"
namespace cougar {

class Spline {
public:
	class Type {
	public:
		Type(std::string value);

		std::string toString();

	private:
		std::string value_;
	};

	Spline();

	// Cubic spline where positions and first derivatives (angle) constraints will
	// be met but second derivatives may be discontinuous.
	static std::shared_ptr<Type> CubicHermite;

	// Quintic spline where positions and first derivatives (angle) constraints
	// will be met, and all second derivatives at knots = 0.
	static std::shared_ptr<Type> QuinticHermite;

	std::shared_ptr<Type> type_;
	double a_;	// ax^5
	double b_;	// + bx^4
	double c_;	// + cx^3
	double d_;	// + dx^2
	double e_;	// + ex
	// f is always 0 for the spline formulation we support.

	// The offset from the world frame to the spline frame.
	// Add these to the output of the spline to obtain world coordinates.
	double y_offset_;
	double x_offset_;
	double knot_distance_;
	double theta_offset_;
	double arc_length_;

	static bool reticulateSplines(std::shared_ptr<WaypointSequence::Waypoint> start,
			std::shared_ptr<WaypointSequence::Waypoint> goal, std::shared_ptr<Spline> result, std::shared_ptr<Type> type);
	static bool reticulateSplines(double x0, double y0, double theta0,
					double x1, double y1, double theta1,
					std::shared_ptr<Spline> result, std::shared_ptr<Type> type);
	double calculateLength();
	double getPercentageForDistance(double distance);
	std::shared_ptr<std::vector<double>> getXandY(double percentage);
	double valueAt(double percentage);
	double angleAt(double percentage);
	double angleChangeAt(double percentage);

	std::string toString();
private:


	static bool almostEqual(double x, double y);
	double derivativeAt(double percentage);
	double secondDerivativeAt(double percentage);

};

} /* namespace cougar */

#endif /* SRC_SPLINE_H_ */
