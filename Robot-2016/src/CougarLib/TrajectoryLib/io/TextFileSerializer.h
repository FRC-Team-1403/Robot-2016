/*
 * TextFileSerializer.h
 *
 *	Created on: Feb 7, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILESERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILESERIALIZER_H_

#include "IPathSerializer.h"
#include "../Trajectory.h"
#include "../Path.h"
#include <cmath>
#include <stdarg.h>
#include <memory>
#include <cstring>

namespace cougar {

class TextFileSerializer : public IPathSerializer {
public:

	/**
	 * Format:
	 *	 PathName
	 *	 NumSegments
	 *	 LeftSegment1
	 *	 ...
	 *	 LeftSegmentN
	 *	 RightSegment1
	 *	 ...
	 *	 RightSegmentN
	 *
	 * Each segment is in the format:
	 *	 pos vel acc jerk heading dt x y
	 *
	 * @param path The path to serialize.
	 * @return A string representation.
	 */
	virtual std::string serialize(std::shared_ptr<Path> path) override;

private:

	virtual std::string serializeTrajectory(std::shared_ptr<Trajectory> trajectory);
	virtual std::string string_format(const std::string fmt_str, ...);
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILESERIALIZER_H_ */
