/*
 * CougarMath.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "CougarMath.h"

namespace cougar {

CougarMath::CougarMath() {
	CougarDebug::debugPrinter(CougarDebug::ISSUE, "CougarMath class being instantiated");
}
CougarMath::~CougarMath() {
	CougarDebug::debugPrinter(CougarDebug::ISSUE, "CougarMath object being destroyed (there shouldn't have been an object in the first place");
}

double CougarMath::getDifferenceInAngleRadians(double from, double to) {
	return boundAngleNegPiToPiRadians(to - from);
}

double CougarMath::getDifferenceInAngleDegrees(double from, double to) {
	return boundAngleNeg180to180Degrees(to - from);
}

double CougarMath::boundAngle0to360Degrees(double angle) {
	// Naive algorithm
	while (angle >= 360.0) {
		angle -= 360.0;
	}
	while (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
}

double CougarMath::boundAngleNeg180to180Degrees(double angle) {
	// Naive algorithm
	while (angle >= 180.0) {
		angle -= 360.0;
	}
	while (angle < -180.0) {
		angle += 360.0;
	}
	return angle;
}

double CougarMath::boundAngle0to2PiRadians(double angle) {
	// Naive algorithm
	while (angle >= 2.0 * M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < 0.0) {
		angle += 2.0 * M_PI;
	}
	return angle;
}

double CougarMath::boundAngleNegPiToPiRadians(double angle) {
	// Naive algorithm
	while (angle >= M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < -M_PI) {
		angle += 2.0 * M_PI;
	}
	return angle;
}

} /* namespace cougar */
