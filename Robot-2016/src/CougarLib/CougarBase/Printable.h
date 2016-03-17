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

#ifndef DISALLOW_COPY_AND_ASSIGN
// Declares private copy constructor and assignment operator in order to
// supress the default implementations of these that the compiler will generate.
// The net effect of this is that someone atetmpting to call them (by accident)
// will cause a linker error due to the unresolevd implementation since they
// are never implemented.
#define DISALLOW_COPY_AND_ASSIGN(TYPE) \
	private:                           \
		TYPE(const TYPE&);             \
		TYPE& operator=(const TYPE&)
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
