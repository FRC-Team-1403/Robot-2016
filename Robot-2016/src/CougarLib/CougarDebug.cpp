/*
 * CougarDebug.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarDebug.h"

namespace cougar {

std::map<int, std::string> CougarDebug::debugLevels;
int CougarDebug::indentation = 0;
bool CougarDebug::didInit = false;
bool CougarDebug::doIndent = true;

CougarDebug::CougarDebug() {}
CougarDebug::~CougarDebug() {}

void CougarDebug::init() {
	if (!debugLevels.empty())
		debugLevels.clear();
	debugLevels[0] = "UNIMPORTANT";
	debugLevels[1] = "MESSAGE";
	debugLevels[2] = "ISSUE";
	debugLevels[3] = "FATAL_ERROR";
	didInit = true;
}

void CougarDebug::debugPrinter(int level, const char *message, ...) {
	std::string tabs = "";
	for (int i = 0; i < indentation; i++) {
		tabs += "\t";
	}
	try {
		message = (tabs + debugLevels.at(level) + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n\n")).c_str();
	} catch (const std::out_of_range& err) {
		if (level < UNIMPORTANT || level > FATAL_ERROR) {
			debugPrinter(MESSAGE, "Invalid debug level passed");
		} else if (debugLevels.empty()) {
			if (didInit) {
				std::cout << "CougarDebug::init did not run correctly. Rerunning now...\n";
			} else {
				std::cout << "CougarDebug::init was not run. Running now...\n";
			}
			init();
		}
		message = (tabs + std::string("UNKNOWN DEBUG LEVEL") + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n\n")).c_str();
	}
	if (level >= DEBUG) {
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}
}

void CougarDebug::debugPrinter(const char *message, ...) {
	std::string tabs = "";
	for (int i = 0; i < indentation; i++) {
		tabs += "\t";
	}
	int level = UNIMPORTANT;
	try {
		message = (tabs + debugLevels.at(level) + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n\n")).c_str();
	} catch (const std::out_of_range& err) {
		if (level < UNIMPORTANT || level > FATAL_ERROR) {
			debugPrinter(MESSAGE, "Invalid debug level passed");
		} else if (debugLevels.empty()) {
			if (didInit) {
				std::cout << "CougarDebug::init did not run correctly. Rerunning now...\n";
			} else {
				std::cout << "CougarDebug::init was not run. Running now...\n";
			}
			init();
		}
		message = (tabs + std::string("UNKNOWN DEBUG LEVEL") + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n\n")).c_str();
	}
	if (level >= DEBUG) {
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}
}

void CougarDebug::debugPrinter(int level, std::string message) {
	debugPrinter(message.c_str(), level);
}

void CougarDebug::debugPrinter(std::string message) {
	debugPrinter(message.c_str(), UNIMPORTANT);
}

void CougarDebug::indent(int amount) {
	indentation += amount;
}

void CougarDebug::unindent(int amount) {
	indentation -= amount;
	if (indentation < 0) {
		indentation = 0;
	}
}

void CougarDebug::startMethod(std::string name) {
	indent();
	debugPrinter(name + std::string(" started"));
}

void CougarDebug::startMethod(const char *name) {
	indent();
	debugPrinter((std::string(name) + std::string(" started")).c_str());
}

void CougarDebug::endMethod(std::string name) {
	unindent();
	debugPrinter(name + " finished");
}

void CougarDebug::endMethod(const char *name) {
	unindent();
	debugPrinter((std::string(name) + std::string(" finished")).c_str());
}

} // namespace cougar
