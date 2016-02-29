/*
 * StateManager.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_
#define SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_

#include "WPILib.h"
#include <memory>
#include <vector>
#include "Dumpable.h"

namespace cougar {

class StateManager {
public:
	static void addObject(std::shared_ptr<Dumpable> obj);
private:

	class StateDumper {
	public:
		StateDumper();
		virtual ~StateDumper();

		virtual void addObjectToDump(std::shared_ptr<Dumpable> obj);
		virtual std::string dump();

		std::shared_ptr<std::vector<std::shared_ptr<Dumpable>>> objectsToDump_;
	};

	StateManager();
	virtual ~StateManager();

	static std::shared_ptr<StateDumper> stateDumper_;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_ */
