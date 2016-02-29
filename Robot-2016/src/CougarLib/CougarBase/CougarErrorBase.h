/*
 * CougarErrorBase.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_COUGARERRORBASE_H_
#define SRC_COUGARLIB_COUGARBASE_COUGARERRORBASE_H_

#include <string>

namespace cougar {

class CougarErrorBase {
public:
	virtual std::string throwFatalError();

	virtual ~CougarErrorBase() = 0;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_COUGARERRORBASE_H_ */
