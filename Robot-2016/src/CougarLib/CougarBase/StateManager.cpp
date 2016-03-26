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

void StateManager::addObject(std::string subsystem, std::shared_ptr<Dumpable> obj) {
	stateDumper_->addObjectToDump(subsystem, obj);
}

std::string StateManager::dump() {
	return stateDumper_->dump();
}

StateManager::StateDumper::StateDumper() {
}

StateManager::StateDumper::~StateDumper() {
}

void StateManager::StateDumper::addObjectToDump(std::string subsystem, std::shared_ptr<Dumpable> obj) {
	if (this->objectsToDump_.find(subsystem) != this->objectsToDump_.end()) {
		this->objectsToDump_.at(subsystem).push_back(obj);
	} else {
		this->objectsToDump_[subsystem] = std::vector<std::shared_ptr<Dumpable>>({obj});
	}
}

std::string StateManager::StateDumper::dump() {
	// lock_guard is fine here because the destructor
	// will be called once this method is over.
	std::lock_guard<std::mutex> guard(stateManagerMutex_);

	std::string dumpTime = std::to_string(Timer::GetFPGATimestamp());
	std::string textToDump = "\n\n***********************\nState dump at " + dumpTime + "\n";

	/*
	for (int i = 0; i < static_cast<int>(this->objectsToDump_.size()); i++) {
		std::shared_ptr<Dumpable> obj = this->objectsToDump_.at(i);

		// If no other references to this object exist, ditch it
		if (obj.use_count() == 1) {
			this->objectsToDump_.erase(this->objectsToDump_.begin() + i);
			i--;
		} else {
			textToDump += obj->dumpState();
			if (textToDump.back() != '\n') {
				textToDump += "\n";
			}
		}
	}
	*/

	for (auto const &iter : this->objectsToDump_) {
		textToDump += "Dumping subsystem " + iter.first + "\n";
		for (auto const &obj : iter.second) {
			textToDump += obj->dumpState();
			if (textToDump.back() != '\n') { // If "\n" is not being appended, do it ourselves
				textToDump += "\n";
			}
		}
		textToDump += "\n\n";
	}

	return textToDump;
}

} /* namespace cougar */
