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
CougarMath::~CougarMath() {}

double CougarMath::getDifferenceInAngleRadians(double from, double to) {
	CougarDebug::startMethod("CougarMath::getDifferenceInAngleRadians");
	return boundAngleNegPiToPiRadians(to - from);
	CougarDebug::endMethod("CougarMath::getDifferenceInAngleRadians");
}

double CougarMath::getDifferenceInAngleDegrees(double from, double to) {
	CougarDebug::startMethod("CougarMath::getDifferenceInAngleDegrees");
	return boundAngleNeg180to180Degrees(to - from);
	CougarDebug::endMethod("CougarMath::getDifferenceInAngleDegrees");
}

double CougarMath::boundAngle0to360Degrees(double angle) {
	CougarDebug::startMethod("CougarMath::boundAngle0to360Degrees");
	// Naive algorithm
	while (angle >= 360.0) {
		angle -= 360.0;
	}
	while (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
	CougarDebug::endMethod("CougarMath::boundAngle0to360Degrees");
}

double CougarMath::boundAngleNeg180to180Degrees(double angle) {
	CougarDebug::startMethod("CougarMath::boundAngleNet180to180Degrees");
	// Naive algorithm
	while (angle >= 180.0) {
		angle -= 360.0;
	}
	while (angle < -180.0) {
		angle += 360.0;
	}
	return angle;
	CougarDebug::endMethod("CougarMath::boundAngleNet180to180Degrees");
}

double CougarMath::boundAngle0to2PiRadians(double angle) {
	CougarDebug::startMethod("CougarMath::boundAngle0to2PiRadians");
	// Naive algorithm
	while (angle >= 2.0 * M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < 0.0) {
		angle += 2.0 * M_PI;
	}
	return angle;
	CougarDebug::endMethod("CougarMath::boundAngle0to2PiRadians");
}

double CougarMath::boundAngleNegPiToPiRadians(double angle) {
	CougarDebug::startMethod("CougarMath::boundAngleNegPitoPiRadians");
	// Naive algorithm
	while (angle >= M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < -M_PI) {
		angle += 2.0 * M_PI;
	}
	CougarDebug::endMethod("CougarMath::boundAngle0to2PiRadians");
	return angle;
}

} /* namespace cougar */
