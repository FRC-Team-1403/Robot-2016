/*
 * CPPStringSerializer.h
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSTRINGSERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSTRINGSERIALIZER_H_

#include "Tokenizer.h"
#include "IPathSerializer.h"
#include "../Path.h"

namespace cougar {



class CPPStringSerializer : public IPathSerializer {
public:

	std::string seralize(std::shared_ptr<Path> path) {
		//std::string contents =
	}

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSTRINGSERIALIZER_H_ */
