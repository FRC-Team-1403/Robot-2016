/*
 * CougarDebug.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarDebug.h"

namespace cougar {

CougarDebug::CougarDebug() {}
CougarDebug::~CougarDebug() {}

void CougarDebug::debugPrinter(int level, const char *message, ...) {
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
}

} // namespace cougar
