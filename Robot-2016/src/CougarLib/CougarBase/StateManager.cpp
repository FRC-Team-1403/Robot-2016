/*
 * StateManager.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "StateManager.h"

namespace cougar {

std::shared_ptr<StateManager::StateDumper> StateManager::stateDumper_ = std::shared_ptr<StateDumper>(new StateDumper());

StateManager::StateManager() {
}

StateManager::~StateManager() {
}

void StateManager::addObject(std::shared_ptr<Dumpable> obj) {
	stateDumper_->addObjectToDump(obj);
}

void StateManager::dump() {
	stateDumper_->dump();
}

StateManager::StateDumper::StateDumper() {
	this->objectsToDump_.reset(new std::vector<std::shared_ptr<Dumpable>>());
}

StateManager::StateDumper::~StateDumper() {
}

void StateManager::StateDumper::addObjectToDump(std::shared_ptr<Dumpable> obj) {
	this->objectsToDump_->push_back(obj);
}

std::string StateManager::StateDumper::dump() {
	// I don't know if we need this. We may
	// be okay without thread locking.
	//std::lock_guard<std::mutex> guard(mutex_);

	std::string dumpTime = std::to_string(Timer::GetFPGATimestamp());
	std::string textToDump = "State dump at " + dumpTime + "\n";
	for (int i = 0; i < static_cast<int>(this->objectsToDump_->size()); i++) {
		std::shared_ptr<Dumpable> obj = this->objectsToDump_->at(i);

		// If no other references to this object exist, ditch it
		if (obj.use_count() == 1) {
			this->objectsToDump_->erase(this->objectsToDump_->begin() + i);
			i--;
		} else {
			textToDump += obj->dumpState();
			if (textToDump.back() != '\n') {
				textToDump += "\n";
			}
		}
	}

	return textToDump;
}

} /* namespace cougar */
