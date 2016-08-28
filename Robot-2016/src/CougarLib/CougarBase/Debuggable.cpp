/*
 * Debuggable.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "Debuggable.h"

namespace cougar {

Debuggable::Debuggable(std::string name) : Dumpable(name) {
	//StateManager::addObject(std::shared_ptr<Dumpable>(this));
}

Debuggable::~Debuggable() {
}

} /* namespace cougar */
