/*
 * IPathDeserializer.h
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHDESERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHDESERIALIZER_H_

#include "../Path.h"

namespace cougar {

class IPathDeserializer {
public:
	virtual std::shared_ptr<Path> deserialize(std::string serialized) = 0;

protected:
	IPathDeserializer();
	virtual ~IPathDeserializer();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHDESERIALIZER_H_ */
