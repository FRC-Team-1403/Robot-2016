/*
 * StateDumper.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarBase/StateDumper.h>

namespace cougar {

StateDumper::StateDumper() {
	this->objectsToDump_.reset(new std::vector<std::shared_ptr<Dumpable>>());
}

StateDumper::~StateDumper() {
}



void StateDumper::addObjectToDump(std::shared_ptr<Dumpable> obj) {
	this->objectsToDump_->push_back(obj);
}

} /* namespace cougar */
