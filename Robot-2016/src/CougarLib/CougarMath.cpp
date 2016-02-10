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
	CougarDebug::debugPrinter("CougarMath::getDifferenceInAngleRadians started");
	return boundAngleNegPiToPiRadians(to - from);
	CougarDebug::debugPrinter("CougarMath::getDifferenceInAngleRadians finished");
}

double CougarMath::getDifferenceInAngleDegrees(double from, double to) {
	CougarDebug::debugPrinter("CougarMath::getDifferenceInAngleDegrees started");
	return boundAngleNeg180to180Degrees(to - from);
	CougarDebug::debugPrinter("CougarMath::getDifferenceInAngleDegrees finished");
}

double CougarMath::boundAngle0to360Degrees(double angle) {
	CougarDebug::debugPrinter("CougarMath::boundAngle0to360Degrees started");
	// Naive algorithm
	while (angle >= 360.0) {
		angle -= 360.0;
	}
	while (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
	CougarDebug::debugPrinter("CougarMath::boundAngle0to360Degrees finished");
}

double CougarMath::boundAngleNeg180to180Degrees(double angle) {
	CougarDebug::debugPrinter("CougarMath::boundAngleNet180to180Degrees started");
	// Naive algorithm
	while (angle >= 180.0) {
		angle -= 360.0;
	}
	while (angle < -180.0) {
		angle += 360.0;
	}
	return angle;
	CougarDebug::debugPrinter("CougarMath::boundAngleNet180to180Degrees finished");
}

double CougarMath::boundAngle0to2PiRadians(double angle) {
	CougarDebug::debugPrinter("CougarMath::boundAngle0to2PiRadians started");
	// Naive algorithm
	while (angle >= 2.0 * M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < 0.0) {
		angle += 2.0 * M_PI;
	}
	return angle;
	CougarDebug::debugPrinter("CougarMath::boundAngle0to2PiRadians finished");
}

double CougarMath::boundAngleNegPiToPiRadians(double angle) {
	CougarDebug::debugPrinter("CougarMath::boundAngleNegPitoPiRadians started");
	// Naive algorithm
	while (angle >= M_PI) {
		angle -= 2.0 * M_PI;
	}
	while (angle < -M_PI) {
		angle += 2.0 * M_PI;
	}
	return angle;
	CougarDebug::debugPrinter("CougarMath::boundAngle0to2PiRadians finished");
}

} /* namespace cougar */
