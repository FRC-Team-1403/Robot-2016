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
#include "TextFileSerializer.h"
#include "../Path.h"
#include <memory>

namespace cougar {

class CPPStringSerializer : public IPathSerializer {
public:

	/*
	 * #pragma once
	 *
	 * #include <CougarLib/TrajectoryLib/Trajectory.h>;
	 * #include <CougarLib/TrajectoryLib/io/TextFileDeserializer.h>
	 * #include <CougarLib/TrajectoryLib/Path.h>
	 * #include <string>
	 * #include <memory>
	 *
	 * namespace cougar {
	 *
	 * class path->getName() : public Path {
	 * public:
	 * 	path->getName() {
	 * 		kSerialized = "tokenizer->next()\n"
	 *			+ "tokenizer->next()\n"
	 *			+...;
	 *		std::shared_ptr<TextFileDeserializer> d(new TextFileDeserializer());
	 *		std::shared_ptr<Path> p = d->deserialize(kSerialized);
	 *		this->name_ = p->getName();
	 *		this->go_left_pair_ = p->getPair();
	 *	}
	 *
	 * private:
	 *	std::string kSerialized;
	 *
	 * };
	 *
	 * } // namespace cougar
	 */
	virtual std::string serialize(std::shared_ptr<Path> path) override;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_TRAJECTORYLIB_IO_CPPSTRINGSERIALIZER_H_ */
