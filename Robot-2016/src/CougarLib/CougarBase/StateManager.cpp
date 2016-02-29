/*
 * StateManager.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarBase/StateManager.h>

namespace cougar {

std::shared_ptr<StateDumper> StateManager::stateDumper_ = std::shared_ptr<StateDumper>(new StateDumper());

StateManager::StateManager() {
	// TODO Auto-generated constructor stub

}

StateManager::~StateManager() {
	// TODO Auto-generated destructor stub
}

void StateManager::addObject(std::shared_ptr<Dumpable> obj) {
	stateDumper_->addObjectToDump(obj);
}

} /* namespace cougar */
