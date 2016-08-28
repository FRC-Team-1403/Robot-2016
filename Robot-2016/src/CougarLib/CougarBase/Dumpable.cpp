/*
 * Dumpable.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "Dumpable.h"

namespace cougar {

Dumpable::Dumpable(std::string name) : Printable(name){

}

Dumpable::~Dumpable() {
}

std::string Dumpable::dumpState() {
	return this->toString();
}

} /* namespace cougar */
