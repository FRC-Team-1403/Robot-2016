/*
 * Printable.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#include "Printable.h"

namespace cougar {

Printable::Printable(std::string name) {
	this->name_ = name;
}

Printable::~Printable() {
}

std::string Printable::toString() {
	return this->name_;
}

} /* namespace cougar */
