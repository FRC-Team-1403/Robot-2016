/*
 * Printable.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_PRINTABLE_H_
#define SRC_COUGARLIB_PRINTABLE_H_

#include <string>

#ifndef REQUIRE_CHILD_IMPLEMENTATION_PRINTABLE
#	define REQUIRE_CHILD_IMPLEMENTATION_PRINTABLE true
#endif

namespace cougar {

class Printable {
public:
	Printable(std::string name);
	virtual ~Printable() = 0;

#	if REQUIRE_CHILD_IMPLEMENTATION_PRINTABLE
		virtual std::string toString() = 0;
#	else
		virtual std::string toString();
#	endif

protected:
	std::string name_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_PRINTABLE_H_ */
