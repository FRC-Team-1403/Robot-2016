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
#include <map>
#include <stdexcept>

namespace cougar {

class CougarDebug {
public:
	static void init();

	static void debugPrinter(int level = UNIMPORTANT, const char *message = "", ...);
	static void debugPrinter(const char *message = "", ...); // If no level is given, it is assumed to be UNIMPORTANT
	static void debugPrinter(int level = UNIMPORTANT, std::string message = "");
	static void debugPrinter(std::string message = "");


	// Messages marked with a debug level higher than
	// or equal to current debug level will be shown.
	// If DEBUG is higher, messages become more verbose.
	enum DEBUG_LEVEL {
		UNIMPORTANT = 0,
		MESSAGE = 1,
		ISSUE = 2,
		FATAL_ERROR = 3
	};
	static const int DEBUG = UNIMPORTANT;

private:
	explicit CougarDebug();
	virtual ~CougarDebug();

	static std::map<int, std::string> debugLevels;
	static bool didInit;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDEBUG_H_ */
