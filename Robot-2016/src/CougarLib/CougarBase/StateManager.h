/*
 * StateManager.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_
#define SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_

#include "StateDumper.h"
#include "Dumpable.h"

namespace cougar {

class StateManager {
public:
	static void addObject(std::shared_ptr<Dumpable> obj);
private:
	StateManager();
	virtual ~StateManager();

	static std::shared_ptr<StateDumper> stateDumper_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_ */
