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
	std::string serialize(std::shared_ptr<Path> path) {
		std::string content = path->getName() + "\n";
		path->goLeft();
		content += path->getLeftWheelTrajectory()->getNumSegments() + "\n";
		content += serializeTrajectory(path->getLeftWheelTrajectory());
		content += serializeTrajectory(path->getRightWheelTrajectory());
		return content;
	}
private:

	std::string serializeTrajectory(std::shared_ptr<Trajectory> trajectory) {
		std::string content = "";
		for (uint32_t i = 0; i < trajectory->getNumSegments(); ++i) {
			std::shared_ptr<Trajectory::Segment> segment = trajectory->getSegment(i);
			content += std::trunc(1000 * segment->pos) * 1000;
			content += string_format(
							"%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
							segment->pos, segment->vel, segment->acc, segment->jerk,
							segment->heading, segment->dt, segment->x, segment->y);
		}
		return content;
	}

	std::string string_format(const std::string fmt_str, ...) {
	    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
	    std::string str;
	    std::unique_ptr<char[]> formatted;
	    va_list ap;
	    while(1) {
	        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
	        strcpy(&formatted[0], fmt_str.c_str());
	        va_start(ap, fmt_str);
	        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
	        va_end(ap);
	        if (final_n < 0 || final_n >= n)
	            n += abs(final_n - n + 1);
	        else
	            break;
	    }
	    return std::string(formatted.get());
	}
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILESERIALIZER_H_ */
