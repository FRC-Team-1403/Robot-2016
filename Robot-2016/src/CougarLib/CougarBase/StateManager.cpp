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
	this->stateDumper_->dump();
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
	std::string dumpTime = std::to_string(Timer::GetFPGATimestamp());
	std::string textToDump = "State dump at " + dumpTime + "\n";
	for (std::shared_ptr<Dumpable> obj : *this->objectsToDump_) {
		obj->dumpState();
	}
}

} /* namespace cougar */
