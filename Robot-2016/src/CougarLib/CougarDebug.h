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

	static void indent(int amount = 1);
	static void unindent(int amount = 1);

	// Used to print out nicely indented method debugging blocks.
	// Should be used in all methods except simple getters.
	// Setter methods should have these as well as a separate debug message
	// stating what value was set to which variable.
	static void startMethod(std::string name);
	static void startMethod(const char *name);
	static void endMethod(std::string name);
	static void endMethod(const char *name);

	// Messages marked with a debug level higher than
	// or equal to current debug level will be shown.
	// If DEBUG is higher, messages become more verbose.
	enum DEBUG_LEVEL {
		UNIMPORTANT = 0,
		MESSAGE = 1,
		ISSUE = 2,
		FATAL_ERROR = 3
	};
	static const int DEBUG = MESSAGE;

private:
	explicit CougarDebug();
	virtual ~CougarDebug();

	static std::map<int, std::string> debugLevels;
	static int indentation;
	static bool didInit;
	static bool doIndent;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDEBUG_H_ */
