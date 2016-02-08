/*
 * TextFileSerializer.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#include <CougarLib/TrajectoryLib/io/TextFileSerializer.h>

namespace cougar {

std::string TextFileSerializer::serialize(std::shared_ptr<Path> path) {
	std::string content = path->getName() + "\n";
	path->goLeft();
	content += path->getLeftWheelTrajectory()->getNumSegments() + "\n";
	content += serializeTrajectory(path->getLeftWheelTrajectory());
	content += serializeTrajectory(path->getRightWheelTrajectory());
	return content;
}

std::string TextFileSerializer::serializeTrajectory(std::shared_ptr<Trajectory> trajectory) {
	std::string content = "";
	for (uint32_t i = 0; i < trajectory->getNumSegments(); ++i) {
		std::shared_ptr<Trajectory::Segment> segment = trajectory->getSegment(i);
		content += string_format(
						"%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
						segment->pos, segment->vel, segment->acc, segment->jerk,
						segment->heading, segment->dt, segment->x, segment->y);
	}
	return content;
}

std::string TextFileSerializer::string_format(const std::string fmt_str, ...) {
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

} /* namespace cougar */
