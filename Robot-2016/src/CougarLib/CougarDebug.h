/*
 * CougarDebug.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 *
 *  The things in this class should really be
 *  "...Log" or "...Logging", not "...Debug",
 *  but it's too late to change that without
 *  breaking everything and making my life harder.
 */

#ifndef SRC_COUGARLIB_COUGARDEBUG_H_
#define SRC_COUGARLIB_COUGARDEBUG_H_

#include <WPILib.h>
#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <string>
#include <map>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "CougarBase/StateManager.h"

namespace cougar {

class CougarDebug {
public:
	// Used to initialize/end CougarDebug (obviously)
	// Used kind of like a constructor and destructor.
	// If logging to a file, init will cause logging to
	// move to a new file and end will close the current file.
	static void init();
	static void end();

	// Print some text out as a debugging statement
	// All statements have an importance level and
	// a message. If no importance level is specified,
	// it is assumed to be UNIMPORTANT. If no message is
	// Specified, it is assumed to be empty. Does formatting
	// just like printf. Can take both C-style or C++ STL strings.
	static void debugPrinter(int level = UNIMPORTANT, const char *message = "", ...);
	static void debugPrinter(const char *message = "", ...);
	static void debugPrinter(int level = UNIMPORTANT, std::string message = "");
	static void debugPrinter(std::string message = "");

	// Changes the indendation level of debug statements.
	// Default amount is one space
	static void indent(int amount = 1);
	static void unindent(int amount = 1);

	// Used to print out nicely indented method debugging blocks.
	// Should be used in all methods except simple getters.
	// Methods that will be called a lot (whether in a simple loop or
	// as a periodic method) probably shouldn't have them either,
	// just to avoid inundating the output stream.
	// Setter methods should have these as well as a separate
	// debug message stating what value was set to which
	// variable. Will always be UNIMPORTANT. For your own sanity,
	// avoid using in TrajectoryLib.
	static void startMethod(std::string name);
	static void startMethod(const char *name);
	static void endMethod(std::string name);
	static void endMethod(const char *name);

	// Messages marked with a debug level higher than
	// or equal to current debug level will be shown.
	// If DEBUG is lower, messages become more verbose.
	enum DEBUG_LEVEL {
		UNIMPORTANT = 0,
		MESSAGE = 1,
		ISSUE = 2,
		FATAL_ERROR = 3
	};

private:
	// Prevent this class from being instantiated
	explicit CougarDebug();
	virtual ~CougarDebug() {}

	static void log(uint8_t level, std::string message);
	static void writeToFile(int8_t level, std::string message);
	static void writeToRiolog(int8_t level, std::string message);

	// This MUST be running in a separate thread,
	// or it will lock up the whole program.
	static void continuouslyDumpStates();

	static FILE *logFile;
	static FILE *dumpFile;
	static std::map<int, std::string> debugLevels;
	static int indentation;
	static bool didInit;
	static bool doIndent;
	static const bool WRITE_TO_RIOLOG = true;
	static const bool WRITE_TO_FILE = true;
	static const bool STATE_DUMPING = true;

	static const int DUMP_INTERVAL_IN_MILLISECONDS = 5000;

	static const int RIOLOG_DEBUG_LEVEL = UNIMPORTANT;
	static const int FILE_DEBUG_LEVEL = UNIMPORTANT;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDEBUG_H_ */
