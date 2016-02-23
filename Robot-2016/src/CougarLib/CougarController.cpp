/*
 * CougarController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarController.h>

namespace cougar {

CougarController::CougarController() {
	CougarDebug::startMethod("CougarController::CougarController");
	CougarDebug::endMethod("CougarController::CougarController");
}

CougarController::~CougarController() {
	//CougarDebug::startMethod("CougarController::~CougarController");
	//CougarDebug::endMethod("CougarController::~CougarController");
}

void CougarController::enable() {
	CougarDebug::startMethod("CougarController::enable");
	enabled = true;
	CougarDebug::endMethod("CougarController::enable");
}

void CougarController::disable() {
	CougarDebug::startMethod("CougarController::disable");
	enabled = false;
	CougarDebug::endMethod("CougarController::disable");
}

bool CougarController::isEnabled() const {
	return enabled;
}

} /* namespace cougar */
