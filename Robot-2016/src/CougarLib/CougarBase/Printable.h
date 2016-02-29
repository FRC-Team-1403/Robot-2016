/*
 * Printable.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_PRINTABLE_H_
#define SRC_COUGARLIB_PRINTABLE_H_

#include <string>

namespace cougar {

class Printable {
public:
	virtual std::string toString() = 0;
	virtual ~Printable() = 0;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_PRINTABLE_H_ */
