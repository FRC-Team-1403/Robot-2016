/*
 * StateDumper.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_STATEDUMPER_H_
#define SRC_COUGARLIB_COUGARBASE_STATEDUMPER_H_

#include <memory>
#include <vector>
#include "Dumpable.h"

namespace cougar {

class StateDumper {
private:
	StateDumper();
	virtual ~StateDumper();

	virtual void addObjectToDump(std::shared_ptr<Dumpable> obj);
	std::shared_ptr<std::vector<std::shared_ptr<Dumpable>>> objectsToDump_;

	std::string dump();

friend StateManager;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_STATEDUMPER_H_ */
