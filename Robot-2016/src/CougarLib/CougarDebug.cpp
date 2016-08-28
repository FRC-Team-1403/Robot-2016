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
std::deque<std::tuple<uint8_t, std::string>> CougarDebug::printQueue;
std::mutex CougarDebug::loggingPrinterMutex_;
std::unique_lock<std::mutex> CougarDebug::printQueueLock_(loggingPrinterMutex_, std::defer_lock);

bool CougarDebug::didInit = false;

CougarDebug::CougarDebug() {}

void CougarDebug::init() {
	internalLog("CougarDebug::init starting");

	printQueueLock_.lock();
	//StateManager::stateDumperLock_.lock();

	if (!debugLevels.empty())
		debugLevels.clear();
	debugLevels[0] = "UNIMPORTANT";
	debugLevels[1] = "MESSAGE";
	debugLevels[2] = "ISSUE";
	debugLevels[3] = "FATAL_ERROR";

	if (WRITE_TO_FILE) {
		system("mkdir -p /home/lvuser/log_files");
		std::string filename = "/home/lvuser/log_files/log_";
		filename += getCurrentTime();
		filename += ".txt";
		std::string create_file_command = "touch " + filename;
		system(create_file_command.c_str());
		std::string change_permissions_command = "chmod 777 " + filename;
		system(change_permissions_command.c_str());
		//logFile = 1;
		logFile = fopen(filename.c_str(), "w");
		fprintf(logFile, (std::string("Writing to file with logging level ") + debugLevels.at(static_cast<int>(FILE_DEBUG_LEVEL)) + "\n\n").c_str());

	}

	if (STATE_DUMPING_TO_FILE) {
		system("mkdir -p /home/lvuser/dump_files");
		std::string filename = "/home/lvuser/dump_files/dump_";
		filename += getCurrentTime();
		filename += ".txt";
		std::string create_file_command = "touch " + filename;
		system(create_file_command.c_str());
		std::string change_permissions_command = "chmod 777 " + filename;
		system(change_permissions_command.c_str());
		//dumpFile = 1;
		dumpFile = fopen(filename.c_str(), "w");
	}

	if (!didInit) {
		std::thread loggingPrinter(throttledLoggingPrinter);
		loggingPrinter.detach();

		std::thread stateDumper(continuouslyDumpStates);
		stateDumper.detach();
	}

	didInit = true;

	printQueueLock_.unlock();
	//StateManager::stateDumperLock_.unlock();

	internalLog("CougarDebug::init finished");
}

void CougarDebug::end() {
	internalLog("CougarDebug::end starting");
	//printQueueLock_.lock();
	//StateManager::stateDumperLock_.lock();
	if (WRITE_TO_FILE) {
		fclose(logFile);
		logFile = NULL;
	}
	if (STATE_DUMPING_TO_FILE) {
		fclose(dumpFile);
		dumpFile = NULL;
	}
	//printQueueLock_.unlock();
	//StateManager::stateDumperLock_.unlock();
	internalLog("CougarDebug::end finished");
}

void CougarDebug::debugPrinter(int level, const char *message, ...) {
	va_list args;
	va_start(args, message);

	char buf[1024];
	vsnprintf(buf, 1024, message, args);

	log(level, std::string(buf));

	va_end(args);
}

void CougarDebug::debugPrinter(const char *message, ...) {
	int level = UNIMPORTANT;
	va_list args;
	va_start(args, message);

	char buf[1024];
	vsnprintf(buf, 1024, message, args);

	log(level, std::string(buf));

	va_end(args);
}

void CougarDebug::debugPrinter(int level, std::string message) {
	debugPrinter(message.c_str(), level);
}

void CougarDebug::debugPrinter(std::string message) {
	debugPrinter(message.c_str(), UNIMPORTANT);
}


void CougarDebug::startMethod(std::string name) {
	debugPrinter(name + std::string(" started "));
}

void CougarDebug::startMethod(const char *name) {
	debugPrinter((std::string(name) + std::string(" started ")).c_str());
}

void CougarDebug::endMethod(std::string name) {
	debugPrinter(name + " finished ");
}

void CougarDebug::endMethod(const char *name) {
	debugPrinter((std::string(name) + std::string(" finished ")).c_str());
}

std::string CougarDebug::getCurrentTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[128];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,128,"%d-%m-%Y %I:%M:%S",timeinfo);
	return std::string(buffer);
}

void CougarDebug::log(uint8_t level, std::string message) {
	std::string local_message = "";
	try {
		local_message += "[" + getCurrentTime() + "] ";
		local_message += "[" + debugLevels.at(level) + "] ";
		local_message += message;
		local_message += "\n";
	} catch (const std::out_of_range& err) {
		if (level < UNIMPORTANT || level > FATAL_ERROR) {
			debugPrinter(MESSAGE, "Invalid debug level passed");
		} else if (debugLevels.empty()) {
			if (didInit) {
				internalLog("CougarDebug::init did not run correctly. Rerunning now...\n");
			} else {
				internalLog("CougarDebug::init was not run. Running now...\n");
			}
			init();
		}
		local_message += "[" + getCurrentTime() + "] ";
		local_message += "[UNKNOWN DEBUG LEVEL] ";
		local_message += message;
		local_message += "\n";
	}
	printQueueLock_.lock();
	printQueue.push_back(std::make_tuple(level, message));
	printQueueLock_.unlock();
}

void CougarDebug::internalLog(std::string message) {
	std::string local_message = "";
	local_message += "[" + getCurrentTime() + "] ";
	local_message += "[CougarDebug Internal Message] ";
	local_message += message;
	local_message += "\n";
	printQueueLock_.lock();
	printQueue.push_back(std::make_tuple(MESSAGE, message));
	printQueueLock_.unlock();
}

void CougarDebug::print(uint8_t level, std::string message) {
	writeToFile(level, message);
	writeToRiolog(level, message);
}

void CougarDebug::writeToFile(uint8_t level, std::string message) {
	if (WRITE_TO_FILE && level >= static_cast<uint8_t>(FILE_DEBUG_LEVEL)) {
		if (logFile != NULL)
			fprintf(logFile, (message + "\n").c_str());
	}
}

void CougarDebug::writeToRiolog(uint8_t level, std::string message) {
	if (WRITE_TO_RIOLOG && level >= static_cast<uint8_t>(RIOLOG_DEBUG_LEVEL)) {
		printf("%s\n", message.c_str());
	}
}

void CougarDebug::throttledLoggingPrinter() {
	// Because this runs forever, we need unique_lock
	// so we can unlock the print queue between runs.
	std::unique_lock<std::mutex> printQueueLock(loggingPrinterMutex_, std::defer_lock);
	auto sleep_time = std::chrono::milliseconds(static_cast<int>(LOGGING_PRINTER_INTERVAL_IN_MILLISECONDS));
	while(WRITE_TO_FILE || WRITE_TO_RIOLOG) {
		printQueueLock.lock();
		for (std::tuple<uint8_t, std::string> pair : printQueue) {
			writeToRiolog(std::get<uint8_t>(pair), std::get<std::string>(pair));
			writeToFile(std::get<uint8_t>(pair), std::get<std::string>(pair));
		}
		printQueue.clear(); // Empty print queue
		printQueueLock.unlock();
		std::this_thread::sleep_for(sleep_time);
	}
}

void CougarDebug::continuouslyDumpStates() {
	auto sleep_time = std::chrono::milliseconds(static_cast<int>(DUMP_INTERVAL_IN_MILLISECONDS));
	while (STATE_DUMPING_TO_RIOLOG || STATE_DUMPING_TO_FILE) {
		if (STATE_DUMPING_TO_RIOLOG) {
			printf("%s", StateManager::dump().c_str());
		}
		if (STATE_DUMPING_TO_FILE) {
			if (dumpFile != NULL)
				fprintf(dumpFile, StateManager::dump().c_str());
		}
		std::this_thread::sleep_for(sleep_time);
	}
}

} // namespace cougar
