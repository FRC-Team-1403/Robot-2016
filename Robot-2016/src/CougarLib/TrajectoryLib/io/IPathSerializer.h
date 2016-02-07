/*
 * IPathSerializer.h
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHSERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHSERIALIZER_H_

#include <string>
#include "../Path.h"

namespace cougar {

class IPathSerializer {
public:
	virtual std::string serialize(Path path) = 0;

private:
	IPathSerializer();
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_IPATHSERIALIZER_H_ */
