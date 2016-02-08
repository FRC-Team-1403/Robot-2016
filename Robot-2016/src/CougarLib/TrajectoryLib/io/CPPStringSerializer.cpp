/*
 * CPPStringSerializer.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: Thejas
 */

#include <CougarLib/TrajectoryLib/io/CPPStringSerializer.h>

namespace cougar {

std::string CPPStringSerializer::serialize(std::shared_ptr<Path> path) {
	std::string contents = "#pragma once\n\n";
	contents += "#include <CougarLib/TrajectoryLib/Trajectory.h>\n";
	contents += "#include <CougarLib/TrajectoryLib/io/TextFileDeserializer.h>\n";
	contents += "#include <CougarLib/TrajectoryLib/Path.h>\n";
	contents += "#include <string>\n";
	contents += "#include <memory>\n\n";
	contents += "namespace cougar {\n\n";
	contents += "class " + path->getName() + " : public Path {\n";
	contents += "public:\n";

	std::shared_ptr<TextFileSerializer> serializer(new TextFileSerializer());
	std::string serialized = serializer->serialize(path);

	std::shared_ptr<Tokenizer> tokenizer(new Tokenizer(serialized, "\n"));

	contents += "\t" + path->getName() + "() {\n";
	contents += "\t\tkSerialized = \"" + tokenizer->next() + "\\n\"\n";
	while (tokenizer->hasMoreTokens()) {
	  contents += "\t\t\t + \"" + tokenizer->next() + "\\n\"";
	  if (tokenizer->hasMoreTokens()) {
		contents += "\n";
	  } else {
		contents += ";\n\n";
	  }
	}
	contents += "\t\tstd::shared_ptr<TextFileDeserializer> d(new TextFileDeserializer());\n";
	contents += "\t\tstd::shared_ptr<Path> p = d->deserialize(kSerialized);\n";
	contents += "\t\tthis->name_ = p->getName();\n";
	contents += "\t\tthis->go_left_pair_ = p->getPair();\n";
	contents += "\t}\n\n";


	contents += "private:\n";
	contents += "\tstd::string kSerialized;\n";

	contents += "};\n\n";
	contents += "} // namespace cougar";

	return contents;
}

} /* namespace cougar */
