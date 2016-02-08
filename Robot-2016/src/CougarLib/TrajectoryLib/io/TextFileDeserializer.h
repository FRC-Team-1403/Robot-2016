/*
 * TextFileDeserializer.h
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILEDESERIALIZER_H_
#define SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILEDESERIALIZER_H_

#include "IPathDeserializer.h"
#include "Tokenizer.h"
#include "../Path.h"
#include "../Trajectory.h"
#include <string>
#include <iostream>
#include <cstdlib>

namespace cougar {

class TextFileDeserializer : public IPathDeserializer {
public:
	virtual std::shared_ptr<Path> deserialize(std::string serialized) override {
		std::shared_ptr<Tokenizer> tokenizer(new Tokenizer(serialized, "\n"));
		std::cout << "Parsing path string\n";
		std::cout << "String has " << serialized.length() << " chars\n";
		std::cout << "Found some tokens\n";

		std::string name = tokenizer->next();
		int num_elements = std::stoi(tokenizer->next());

		std::shared_ptr<Trajectory> left(new Trajectory(num_elements));
		for (int i = 0; i < num_elements; ++i) {
			std::shared_ptr<Trajectory::Segment> segment(new Trajectory::Segment());
			std::shared_ptr<Tokenizer> line_tokenizer(new Tokenizer(tokenizer->next(), " "));

			segment->pos = std::stod(line_tokenizer->next());
			segment->vel = std::stod(line_tokenizer->next());
			segment->acc = std::stod(line_tokenizer->next());
			segment->jerk = std::stod(line_tokenizer->next());
			segment->heading = std::stod(line_tokenizer->next());
			segment->dt = std::stod(line_tokenizer->next());
			segment->x = std::stod(line_tokenizer->next());
			segment->y = std::stod(line_tokenizer->next());

			left->setSegment(i, segment);
		}

		std::shared_ptr<Trajectory> right(new Trajectory(num_elements));
		for (int i = 0; i < num_elements; ++i) {
			std::shared_ptr<Trajectory::Segment> segment(new Trajectory::Segment());
			std::shared_ptr<Tokenizer> line_tokenizer(new Tokenizer(tokenizer->next(), " "));

			segment->pos = std::stod(line_tokenizer->next());
			segment->vel = std::stod(line_tokenizer->next());
			segment->acc = std::stod(line_tokenizer->next());
			segment->jerk = std::stod(line_tokenizer->next());
			segment->heading = std::stod(line_tokenizer->next());
			segment->dt = std::stod(line_tokenizer->next());
			segment->x = std::stod(line_tokenizer->next());
			segment->y = std::stod(line_tokenizer->next());

			right->setSegment(i, segment);
		}

		std::cout << "...finished parsing path from string\n";
		return std::shared_ptr<Path>(new Path(name, std::shared_ptr<Trajectory::Pair>(new Trajectory::Pair(left, right))));
	}
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_TEXTFILEDESERIALIZER_H_ */
