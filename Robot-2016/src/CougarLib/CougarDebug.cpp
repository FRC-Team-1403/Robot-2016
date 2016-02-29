/*
 * CougarDebug.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#include "CougarDebug.h"

namespace cougar {

FILE *CougarDebug::logFile;
FILE *CougarDebug::dumpFile;
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
		logFile = fopen(filename.c_str(), "w");
	}

	if (STATE_DUMPING) {
		system("mkdir -p /home/lvuser/dump_files");
		uint64_t milliseconds_since_epoch =
			std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		std::string filename = "/home/lvuser/dump_files/dump_" + std::to_string(milliseconds_since_epoch) + ".txt";
		std::string create_file_command = "touch " + filename;
		system(create_file_command.c_str());
		std::string change_permissions_command = "chmod 777 " + filename;
		system(change_permissions_command.c_str());
		dumpFile = fopen(filename.c_str(), "w");

		std::thread stateDumper(continuouslyDumpStates);
		stateDumper.detach();
	}

	std::cout << "CougarDebug::init finished\n";
}

void CougarDebug::end() {
	std::cout << "CougarDebug::end starting\n";
	if (WRITE_TO_FILE) {
		fclose(logFile);
		//delete logFile;
	}
	std::cout << "CougarDebug::end finished\n";
}

void CougarDebug::debugPrinter(int level, const char *message, ...) {
	va_list args;
	va_start(args, message);

	char buf[strlen(message) * 2];
	vsprintf(buf, message, args);
	std::string strMessage = std::string(buf);

	std::thread loggingThread(log, level, strMessage);
	loggingThread.detach();
	va_end(args);
}

void CougarDebug::debugPrinter(const char *message, ...) {
	int level = UNIMPORTANT;
	va_list args;
	va_start(args, message);

	char buf[strlen(message) * 2];
	vsprintf(buf, message, args);
	std::string strMessage = std::string(buf);

	std::thread loggingThread(log, level, strMessage);
	loggingThread.detach();
	va_end(args);
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

void CougarDebug::log(uint8_t level, std::string message) {
	std::string tabs = "";
	for (int i = 0; i < indentation; i++) {
		tabs += "  ";
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
	writeToFile(level, message);
	writeToRiolog(level, message);
}

void CougarDebug::writeToFile(int8_t level, std::string message) {
	if (WRITE_TO_FILE && level > FILE_DEBUG_LEVEL) {
		std::thread fileWriter(fprintf, logFile, message.c_str());
		fileWriter.detach();
	}
}

void CougarDebug::writeToRiolog(int8_t level, std::string message) {
	if (WRITE_TO_RIOLOG && level > RIOLOG_DEBUG_LEVEL) {
		std::thread riologWriter(printf, "%s", message.c_str());
		riologWriter.detach();
	}
}

void CougarDebug::continuouslyDumpStates() {
	while (STATE_DUMPING) {
		StateManager::dump();
		std::this_thread::sleep_for(std::chrono::milliseconds(DUMP_INTERVAL_IN_MILLISECONDS));
	}
}

} // namespace cougar
