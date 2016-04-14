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
	this->value_ = value;
}

std::string Spline::Type::toString() {
	return value_;
}

Spline::Spline() {
	// All splines should be made via the static interface
	arc_length_ = -1;
}

bool Spline::reticulateSplines(std::shared_ptr<WaypointSequence::Waypoint> start,
		std::shared_ptr<WaypointSequence::Waypoint> goal, std::shared_ptr<Spline> result, std::shared_ptr<Type> type) {
	return reticulateSplines(start->x, start->y, start->theta, goal->x, goal->y,
					goal->theta, result, type);
}

bool Spline::reticulateSplines(double x0, double y0, double theta0,
				double x1, double y1, double theta1,
				std::shared_ptr<Spline> result, std::shared_ptr<Type> type) {
	result->type_ = type;

	// Transform x to the origin
	result->x_offset_ = x0;
	result->y_offset_ = y0;
	double x1_hat = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	if (x1_hat == 0) {
		CougarDebug::debugPrinter(CougarDebug::FATAL_ERROR, "reticulateSplines failed - CASE 1");
		return false;
	}
	result->knot_distance_ = x1_hat;
	result->theta_offset_ = atan2(y1 - y0, x1 - x0);
	double theta0_hat = CougarMath::getDifferenceInAngleRadians(
					result->theta_offset_, theta0);
	double theta1_hat = CougarMath::getDifferenceInAngleRadians(
					result->theta_offset_, theta1);

	// We cannot handle vertical slopes in our rotated, translated basis.
	// This would mean the user wants to end up 90 degrees off of the straight
	// line between p0 and p1.
	if (almostEqual(abs(theta0_hat), M_PI / 2)
					|| almostEqual(abs(theta1_hat), M_PI / 2)) {
		CougarDebug::debugPrinter(CougarDebug::FATAL_ERROR, "reticulateSplines failed - CASE 2");
		return false;
	}
	// We also cannot handle the case that the end angle is facing towards the
	// start angle (total turn > 90 degrees).
	if (abs(CougarMath::getDifferenceInAngleRadians(theta0_hat,
					theta1_hat))
					>= M_PI / 2) {
		CougarDebug::debugPrinter(CougarDebug::FATAL_ERROR, "reticulateSplines failed - CASE 3");
		return false;
	}
	// Turn angles into derivatives (slopes)
	double yp0_hat = tan(theta0_hat);
	double yp1_hat = tan(theta1_hat);
	if (type == CubicHermite) {
		// Calculate the cubic spline coefficients
		result->a_ = 0;
		result->b_ = 0;
		result->c_ = (yp1_hat + yp0_hat) / (x1_hat * x1_hat);
		result->d_ = -(2 * yp0_hat + yp1_hat) / x1_hat;
		result->e_ = yp0_hat;
	} else if (type == QuinticHermite) {
		result->a_ = -(3 * (yp0_hat + yp1_hat)) / (x1_hat * x1_hat * x1_hat * x1_hat);
		result->b_ = (8 * yp0_hat + 7 * yp1_hat) / (x1_hat * x1_hat * x1_hat);
		result->c_ = -(6 * yp0_hat + 4 * yp1_hat) / (x1_hat * x1_hat);
		result->d_ = 0;
		result->e_ = yp0_hat;
	}
	return true;
}

double Spline::calculateLength() {
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

	return arc_length_;
}

double Spline::getPercentageForDistance(double distance) {
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

	return result;
}

double Spline::valueAt(double percentage) {
	percentage = fmax(fmin(percentage, 1), 0);
	double x_hat = percentage * knot_distance_;
	double y_hat = (a_ * x_hat + b_) * x_hat * x_hat * x_hat * x_hat
					+ c_ * x_hat * x_hat * x_hat + d_ * x_hat * x_hat + e_ * x_hat;

	double cos_theta = cos(theta_offset_);
	double sin_theta = sin(theta_offset_);

	double value = x_hat * sin_theta + y_hat * cos_theta + y_offset_;

	return value;
}

double Spline::angleAt(double percentage) {
	double angle = CougarMath::boundAngle0to2PiRadians(
					atan(derivativeAt(percentage)) + theta_offset_);
	return angle;
}

double Spline::angleChangeAt(double percentage) {
	return CougarMath::boundAngleNegPiToPiRadians(
					atan(secondDerivativeAt(percentage)));
}

std::string Spline::toString() {
	return std::string("a=") + std::to_string(a_) + "; b=" + std::to_string(b_) + "; c=" + std::to_string(c_) + "; d=" + std::to_string(d_) + "; e=" + std::to_string(e_);
}

bool Spline::almostEqual(double x, double y) {
	return abs(x - y) < 1E-6;
}

double Spline::derivativeAt(double percentage) {
	percentage = fmax(fmin(percentage, 1), 0);

	double x_hat = percentage * knot_distance_;
	double yp_hat = (5 * a_ * x_hat + 4 * b_) * x_hat * x_hat * x_hat + 3 * c_ * x_hat * x_hat
					+ 2 * d_ * x_hat + e_;

	return yp_hat;
}

double Spline::secondDerivativeAt(double percentage) {
	percentage = fmax(fmin(percentage, 1), 0);

	double x_hat = percentage * knot_distance_;
	double ypp_hat = (20 * a_ * x_hat + 12 * b_) * x_hat * x_hat + 6 * c_ * x_hat + 2 * d_;

	return ypp_hat;
}


} /* namespace cougar */
