/*
 * CougarDebug.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARDEBUG_H_
#define SRC_COUGARLIB_COUGARDEBUG_H_

#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace cougar {

class CougarDebug {
public:
	static void debugPrinter(const char *message, ...);

	static const bool DEBUG = false;

private:
	explicit CougarDebug();
	virtual ~CougarDebug();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARDEBUG_H_ */
