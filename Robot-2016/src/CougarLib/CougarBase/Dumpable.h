/*
 * Dumpable.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_DUMPABLE_H_
#define SRC_COUGARLIB_DUMPABLE_H_

#include "Printable.h"
#include <string>

namespace cougar {

class Dumpable : Printable {
public:
	virtual std::string dumpState() = 0;
	virtual ~Dumpable() = 0;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_DUMPABLE_H_ */
