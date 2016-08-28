/*
 * CougarCougarSubsystem.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: Thejas
 */

#include "CougarSubsystem.h"

namespace cougar {

CougarSubsystem::CougarSubsystem(const std::string name) : Subsystem(name) {

}

void CougarSubsystem::addObject(std::shared_ptr<Dumpable> obj) {
	StateManager::addObject(this->GetName(), obj);
}

} /* namespace cougar */
