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

#ifndef REQUIRE_CHILD_IMPLEMENTATION_DUMPABLE
#	define REQUIRE_CHILD_IMPLEMENTATION_DUMPABLE true
#endif

namespace cougar {

class Dumpable : public Printable {
public:
	virtual ~Dumpable() = 0;

#	if REQUIRE_CHILD_IMPLEMENTATION_DUMPABLE
		virtual std::string dumpState() = 0;
#	else
		virtual std::string dumpState();
#	endif
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_DUMPABLE_H_ */
