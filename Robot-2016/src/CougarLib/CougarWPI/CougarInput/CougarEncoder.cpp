/*
 * CougarEncoder.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarWPI/CougarInput/CougarEncoder.h>

namespace cougar {

CougarEncoder::CougarEncoder(uint32_t aChannel, uint32_t bChannel, std::string name, bool reverseDirection,
	          EncodingType encodingType)
			: Encoder(aChannel, bChannel, reverseDirection, encodingType), Debuggable(name) {
}

CougarEncoder::CougarEncoder(std::shared_ptr<DigitalSource> aSource,
		std::shared_ptr<DigitalSource> bSource, std::string name,
		bool reverseDirection, EncodingType encodingType)
		: Encoder(aSource, bSource), Debuggable(name) {
}

CougarEncoder::CougarEncoder(DigitalSource *aSource, DigitalSource *bSource, std::string name,
		bool reverseDirection, EncodingType encodingType)
		: Encoder(aSource, bSource, reverseDirection, encodingType), Debuggable(name) {
}

CougarEncoder::CougarEncoder(DigitalSource &aSource, DigitalSource &bSource, std::string name,
		bool reverseDirection, EncodingType encodingType)
		: Encoder(aSource, bSource, reverseDirection, encodingType), Debuggable(name) {
}

CougarEncoder::~CougarEncoder() {}

std::string CougarEncoder::toString() {
	std::string str = "CougarEncoder " + this->name_ + "\n";
	return str;
}

std::string CougarEncoder::dumpState() {
	std::string str = this->toString();
	str += "Distance: " + std::to_string(this->GetDistance());
	str += "Rate: " + std::to_string(this->GetRate());
	return str;
}

} /* namespace cougar */
