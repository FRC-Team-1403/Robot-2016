/*
 * Debuggable.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_DEBUGGABLE_H_
#define SRC_COUGARLIB_DEBUGGABLE_H_

#include "Dumpable.h"
#include "StateManager.h"

namespace cougar {

class Debuggable : public Dumpable {
public:
	Debuggable();
	//virtual void
	virtual ~Debuggable() = 0;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_DEBUGGABLE_H_ */
