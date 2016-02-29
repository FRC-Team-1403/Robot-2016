/*
 * Debuggable.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "Debuggable.h"

namespace cougar {

Debuggable::Debuggable() {
	StateManager::addObject(std::shared_ptr<Dumpable>(this));
}

Debuggable::~Debuggable() {
	// TODO Auto-generated destructor stub
}

} /* namespace cougar */
