/*
 * CougarEncoder.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarWPI/CougarInput/CougarEncoder.h>

namespace cougar {

CougarEncoder::CougarEncoder(uint32_t aChannel, uint32_t bChannel, bool reverseDirection /* = false */, Encoder::EncodingType encodingType /* = Encoder::k4X */) {
	std::shared_ptr<Encoder> tmpEncoder(new Encoder(aChannel, bChannel, reverseDirection, encodingType));
	this->encoder_ = tmpEncoder;
}

CougarEncoder::~CougarEncoder() {
	// TODO Auto-generated destructor stub
}

} /* namespace cougar */
