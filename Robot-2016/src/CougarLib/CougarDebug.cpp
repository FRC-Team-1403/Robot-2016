/*
 * CougarDebug.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarDebug.h"

namespace cougar {

FILE *CougarDebug::logFile;
std::map<int, std::string> CougarDebug::debugLevels;
int CougarDebug::indentation = 0;
bool CougarDebug::didInit = false;
bool CougarDebug::doIndent = true;

CougarDebug::CougarDebug() {}

void CougarDebug::init() {
	std::cout << "CougarDebug::init starting\n";
	if (!debugLevels.empty())
		debugLevels.clear();
	debugLevels[0] = "UNIMPORTANT";
	debugLevels[1] = "MESSAGE";
	debugLevels[2] = "ISSUE";
	debugLevels[3] = "FATAL_ERROR";
	didInit = true;

	if (WRITE_TO_FILE) {
		system("mkdir -p /home/lvuser/log_files");
		uint64_t milliseconds_since_epoch =
		    std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		std::string filename = "/home/lvuser/log_files/log_" + std::to_string(milliseconds_since_epoch) + ".txt";
		std::string create_file_command = "touch " + filename;
		system(create_file_command.c_str());
		std::string change_permissions_command = "chmod 777 " + filename;
		system(change_permissions_command.c_str());
		logFile = fopen(filename.c_str(), "rw");
	}
	std::cout << "CougarDebug::init finished\n";
}

void CougarDebug::end() {
	std::cout << "CougarDebug::end starting\n";
	if (WRITE_TO_FILE) {
		fclose(logFile);
		delete logFile;
	}
	std::cout << "CougarDebug::init finished\n";
}

void CougarDebug::debugPrinter(int level, const char *message, ...) {
	if (level >= DEBUG) {
		std::string tabs = "";
		for (int i = 0; i < indentation; i++) {
			tabs += " ";
		}
		try {
			message = (tabs + debugLevels.at(level) + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n")).c_str();
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
			message = (tabs + std::string("UNKNOWN DEBUG LEVEL") + std::string(": ") + std::string(message) + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp()) + std::string("\n")).c_str();
		}

		va_list args;
		va_start(args, message);
		if (WRITE_TO_RIOLOG)
			vprintf(message, args);
		if (WRITE_TO_FILE)
			vfprintf(logFile, message, args);
		va_end(args);
	}
}

void CougarDebug::debugPrinter(const char *message, ...) {
	int level = UNIMPORTANT;
	if (level >= DEBUG) {
		std::string tabs = "";
		for (int i = 0; i < indentation; i++) {
			tabs += " ";
		}
		try {
			message = (tabs + debugLevels.at(level) + std::string(": ") + std::string(message)/* + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp())*/ + std::string("\n")).c_str();
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
			message = (tabs + std::string("UNKNOWN DEBUG LEVEL") + std::string(": ") + std::string(message)/* + std::string(" at time ") + std::to_string(Timer::GetFPGATimestamp())*/ + std::string("\n")).c_str();
		}
		va_list args;
		va_start(args, message);
		if (WRITE_TO_RIOLOG)
			vprintf(message, args);
		if (WRITE_TO_FILE)
			vfprintf(logFile, message, args);
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
