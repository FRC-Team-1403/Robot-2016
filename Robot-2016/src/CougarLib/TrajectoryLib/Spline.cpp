/*
 * Spline.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "Spline.h"

namespace cougar {

std::shared_ptr<Spline::Type> Spline::CubicHermite = std::shared_ptr<Type>(new Type("CubicHermite"));
std::shared_ptr<Spline::Type> Spline::QuinticHermite = std::shared_ptr<Type>(new Type("QuinticHermite"));

Spline::Type::Type(std::string value) {
	//CougarDebug::startMethod("Spline::Type::Type");
	this->value_ = value;
	//CougarDebug::endMethod("Spline::Type::Type");
}

std::string Spline::Type::toString() {
	//CougarDebug::startMethod("Spline::Type::toString");
	//CougarDebug::endMethod("Spline::Type::toString");
	return value_;


}

Spline::Spline() {
	//CougarDebug::startMethod("Spline::Spline");
	// All splines should be made via the static interface
	arc_length_ = -1;
	//CougarDebug::endMethod("Spline::Spline");
}

bool Spline::reticulateSplines(std::shared_ptr<WaypointSequence::Waypoint> start,
		std::shared_ptr<WaypointSequence::Waypoint> goal, std::shared_ptr<Spline> result, std::shared_ptr<Type> type) {
	//CougarDebug::startMethod("Spline::reticulateSplines");
	//CougarDebug::endMethod("Spline::reticulateSplines");
	return reticulateSplines(start->x, start->y, start->theta, goal->x, goal->y,
					goal->theta, result, type);


}

bool Spline::reticulateSplines(double x0, double y0, double theta0,
				double x1, double y1, double theta1,
				std::shared_ptr<Spline> result, std::shared_ptr<Type> type) {
	//CougarDebug::startMethod("Spline::reticulateSplines");
	//CougarDebug::debugPrinter("Spline::reticulateSplines started");
	result->type_ = type;

	// Transform x to the origin
	result->x_offset_ = x0;
	result->y_offset_ = y0;
	double x1_hat = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	if (x1_hat == 0) {
		return false;
	}
	//CougarDebug::debugPrinter("Spline::reticulateSplines checkpoint 1");
	result->knot_distance_ = x1_hat;
	result->theta_offset_ = atan2(y1 - y0, x1 - x0);
	double theta0_hat = CougarMath::getDifferenceInAngleRadians(
					result->theta_offset_, theta0);
	double theta1_hat = CougarMath::getDifferenceInAngleRadians(
					result->theta_offset_, theta1);

	//CougarDebug::debugPrinter("Spline::reticulateSplines checkpoint 2");
	// We cannot handle vertical slopes in our rotated, translated basis.
	// This would mean the user wants to end up 90 degrees off of the straight
	// line between p0 and p1.
	if (almostEqual(abs(theta0_hat), M_PI / 2)
					|| almostEqual(abs(theta1_hat), M_PI / 2)) {
		return false;
	}
	// We also cannot handle the case that the end angle is facing towards the
	// start angle (total turn > 90 degrees).
	if (abs(CougarMath::getDifferenceInAngleRadians(theta0_hat,
					theta1_hat))
					>= M_PI / 2) {
		return false;
	}
	//CougarDebug::debugPrinter("Spline::reticulateSplines checkpoint 3");
	// Turn angles into derivatives (slopes)
	double yp0_hat = tan(theta0_hat);
	double yp1_hat = tan(theta1_hat);
	//CougarDebug::debugPrinter("Spline::reticulateSplines checkpoint 4");
	if (type == CubicHermite) {
		// Calculate the cubic spline coefficients
		//CougarDebug::debugPrinter("Cubic Hermite");
		result->a_ = 0;
		result->b_ = 0;
		result->c_ = (yp1_hat + yp0_hat) / (x1_hat * x1_hat);
		result->d_ = -(2 * yp0_hat + yp1_hat) / x1_hat;
		result->e_ = yp0_hat;
	} else if (type == QuinticHermite) {
		//CougarDebug::debugPrinter("Quintic Hermite");
		result->a_ = -(3 * (yp0_hat + yp1_hat)) / (x1_hat * x1_hat * x1_hat * x1_hat);
		result->b_ = (8 * yp0_hat + 7 * yp1_hat) / (x1_hat * x1_hat * x1_hat);
		result->c_ = -(6 * yp0_hat + 4 * yp1_hat) / (x1_hat * x1_hat);
		result->d_ = 0;
		result->e_ = yp0_hat;
	}
	//CougarDebug::endMethod("Spline::reticulateSplines");
	return true;
}

double Spline::calculateLength() {
	//CougarDebug::startMethod("Spline::calculateLength");

	if (arc_length_ >= 0) {
		return arc_length_;
	}

	const int kNumSamples = 100000;
	double arc_length = 0;
	double t, dydt;
	double integrand, last_integrand
					= sqrt(1 + derivativeAt(0) * derivativeAt(0)) / kNumSamples;
	for (int i = 1; i <= kNumSamples; ++i) {
		t = ((double) i) / kNumSamples;
		dydt = derivativeAt(t);
		integrand = sqrt(1 + dydt * dydt) / kNumSamples;
		arc_length += (integrand + last_integrand) / 2;
		last_integrand = integrand;
	}
	arc_length_ = knot_distance_ * arc_length;
	//CougarDebug::endMethod("Spline::calculateLength");

	return arc_length_;
}

double Spline::getPercentageForDistance(double distance) {
	//CougarDebug::startMethod("Spline::getPercentageForDistance");

	const int kNumSamples = 100000;
	double arc_length = 0;
	double t = 0;
	double last_arc_length = 0;
	double dydt;
	double integrand, last_integrand
					= sqrt(1 + derivativeAt(0) * derivativeAt(0)) / kNumSamples;
	distance /= knot_distance_;
	for (int i = 1; i <= kNumSamples; ++i) {
		t = ((double) i) / kNumSamples;
		dydt = derivativeAt(t);
		integrand = sqrt(1 + dydt * dydt) / kNumSamples;
		arc_length += (integrand + last_integrand) / 2;
		if (arc_length > distance) {
			break;
		}
		last_integrand = integrand;
		last_arc_length = arc_length;
	}

	// Interpolate between samples.
	double interpolated = t;
	if (arc_length != last_arc_length) {
		interpolated += ((distance - last_arc_length)
						/ (arc_length - last_arc_length) - 1) / (double) kNumSamples;
	}

	return interpolated;
}

std::shared_ptr<std::vector<double>> Spline::getXandY(double percentage) {

	std::shared_ptr<std::vector<double>> result(new std::vector<double>());

	percentage = fmax(fmin(percentage, 1), 0);
	double x_hat = percentage * knot_distance_;
	double y_hat = (a_ * x_hat + b_) * x_hat * x_hat * x_hat * x_hat
					+ c_ * x_hat * x_hat * x_hat + d_ * x_hat * x_hat + e_ * x_hat;

	double cos_theta = cos(theta_offset_);
	double sin_theta = sin(theta_offset_);

	result->push_back(x_hat * cos_theta - y_hat * sin_theta + x_offset_);
	result->push_back(x_hat * sin_theta + y_hat * cos_theta + y_offset_);

	//CougarDebug::endMethod("Spline::getPercentageForDistance");
	return result;
}

double Spline::valueAt(double percentage) {
	//CougarDebug::startMethod("Spline::valueAt");

	percentage = fmax(fmin(percentage, 1), 0);
	double x_hat = percentage * knot_distance_;
	double y_hat = (a_ * x_hat + b_) * x_hat * x_hat * x_hat * x_hat
					+ c_ * x_hat * x_hat * x_hat + d_ * x_hat * x_hat + e_ * x_hat;

	double cos_theta = cos(theta_offset_);
	double sin_theta = sin(theta_offset_);

	double value = x_hat * sin_theta + y_hat * cos_theta + y_offset_;

	//CougarDebug::endMethod("Spline::valueAt");
	return value;
}

double Spline::angleAt(double percentage) {
	//CougarDebug::startMethod("Spline::angleAt");

	double angle = CougarMath::boundAngle0to2PiRadians(
					atan(derivativeAt(percentage)) + theta_offset_);
	//CougarDebug::endMethod("Spline::angleAt");
	return angle;
}

double Spline::angleChangeAt(double percentage) {
	//CougarDebug::startMethod("Spline::angleChangeAt");
	//CougarDebug::endMethod("Spline::angleChangeAt");
	return CougarMath::boundAngleNegPiToPiRadians(
					atan(secondDerivativeAt(percentage)));
}

std::string Spline::toString() {
	//CougarDebug::startMethod("Spline::toString");
	//CougarDebug::endMethod("Spline::toString");
	return std::string("a=") + std::to_string(a_) + "; b=" + std::to_string(b_) + "; c=" + std::to_string(c_) + "; d=" + std::to_string(d_) + "; e=" + std::to_string(e_);
}

bool Spline::almostEqual(double x, double y) {
	//CougarDebug::startMethod("Spline::almostEqual");
	//CougarDebug::endMethod("Spline::almostEqual");
	return abs(x - y) < 1E-6;
}

double Spline::derivativeAt(double percentage) {
	//CougarDebug::startMethod("Spline::derivativeAt");

	percentage = fmax(fmin(percentage, 1), 0);

	double x_hat = percentage * knot_distance_;
	double yp_hat = (5 * a_ * x_hat + 4 * b_) * x_hat * x_hat * x_hat + 3 * c_ * x_hat * x_hat
					+ 2 * d_ * x_hat + e_;

	//CougarDebug::endMethod("Spline::derivativeAt");
	return yp_hat;
}

double Spline::secondDerivativeAt(double percentage) {
	//CougarDebug::startMethod("Spline::secondDerivativeAt");
	percentage = fmax(fmin(percentage, 1), 0);

	double x_hat = percentage * knot_distance_;
	double ypp_hat = (20 * a_ * x_hat + 12 * b_) * x_hat * x_hat + 6 * c_ * x_hat + 2 * d_;

	//CougarDebug::endMethod("Spline::secondDerivativeAt");
	return ypp_hat;
}


} /* namespace cougar */
