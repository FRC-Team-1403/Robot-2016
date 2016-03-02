/*
 * Debuggable.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "Debuggable.h"

namespace cougar {

Debuggable::Debuggable(std::string name, bool willDump) : Dumpable(name) {
	// Some objects may be part of other objects and should be
	// dumped along with the enclosing object, not separately.
	if (willDump) {
		StateManager::addObject(std::shared_ptr<Dumpable>(this));
	}
}

Debuggable::~Debuggable() {
}

} /* namespace cougar */
