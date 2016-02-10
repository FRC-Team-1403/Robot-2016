/*
 * CougarMath.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARMATH_H_
#define SRC_COUGARMATH_H_

#include <cmath>
#include "CougarDebug.h"

namespace cougar {

class CougarMath {
public:
	// constants


	/**
	* Get the difference in angle between two angles.
	*
	* @param from The first angle
	* @param to The second angle
	* @return The change in angle from the first argument necessary to line up
	* with the second. Always between -Pi and Pi
	*/
	static double getDifferenceInAngleRadians(double from, double to);
	/**
	* Get the difference in angle between two angles.
	*
	* @param from The first angle
	* @param to The second angle
	* @return The change in angle from the first argument necessary to line up
	* with the second. Always between -180 and 180
	*/
	static double getDifferenceInAngleDegrees(double from, double to);
	static double boundAngle0to360Degrees(double angle);
	static double boundAngleNeg180to180Degrees(double angle);
	static double boundAngle0to2PiRadians(double angle);
	static double boundAngleNegPiToPiRadians(double angle);

private:
	CougarMath();
	virtual ~CougarMath();
};

} /* namespace cougar */

#endif /* SRC_COUGARMATH_H_ */
