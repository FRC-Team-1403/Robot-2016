/*
 * CougarDebug.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDEBUG_H_
#define SRC_COUGARLIB_COUGARDEBUG_H_

#include <WPILib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace cougar {

class CougarDebug {
public:
	static void debugPrinter(int level, const char *message, ...);

	// Messages marked with a debug level higher than
	// or equal to current debug level will be shown.
	// If DEBUG is higher, messages become more verbose.
	enum DEBUG_LEVEL {
		MESSAGE = 1,
		ISSUE = 2,
		FATAL_ERROR = 3
	};
	static const int DEBUG = MESSAGE;

private:
	explicit CougarDebug();
	virtual ~CougarDebug();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDEBUG_H_ */
