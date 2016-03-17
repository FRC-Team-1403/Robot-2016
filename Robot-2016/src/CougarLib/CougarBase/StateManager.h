/*
 * StateManager.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 *
 */

#ifndef SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_
#define SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_

#include "WPILib.h"
#include <memory>
#include <vector>
#include <mutex>
#include <map>
#include "Dumpable.h"
#include "CougarSubsystem.h"

namespace cougar {

class StateManager {
public:
	static void addObject(std::string subsystem, std::shared_ptr<Dumpable> obj);
	static std::string dump();

private:

	class StateDumper {
	public:
		StateDumper();
		virtual ~StateDumper();

		virtual void addObjectToDump(std::string subsystem, std::shared_ptr<Dumpable> obj);
		virtual std::string dump();

		std::map<std::string, std::vector<std::shared_ptr<Dumpable>>> objectsToDump_;
		std::mutex stateManagerMutex_;
	};

	StateManager();
	virtual ~StateManager();

	static std::shared_ptr<StateDumper> stateDumper_;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_STATEMANAGER_H_ */
