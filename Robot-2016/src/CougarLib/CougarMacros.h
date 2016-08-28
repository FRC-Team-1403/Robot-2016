/*
 * CougarMacros.h
 *
 *  Created on: Apr 1, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARMACROS_H_
#define SRC_COUGARLIB_COUGARMACROS_H_

#ifndef DISALLOW_COPY_AND_ASSIGN
// Declares private copy constructor and assignment operator in order to
// suppress the default implementations of these that the compiler will generate.
// The net effect of this is that someone attempting to call them (by accident)
// will cause a linker error due to the unresolved implementation since they
// are never implemented.

// Forget this for now
#define DISALLOW_COPY_AND_ASSIGN(TYPE) \
	private:                           \
		explicit TYPE(const TYPE&);             \
		/*TYPE(TYPE *);				   */\
		/*TYPE(std::shared_ptr<TYPE>);   */\
		TYPE& operator=(const TYPE&);
#endif

#endif /* SRC_COUGARLIB_COUGARMACROS_H_ */
