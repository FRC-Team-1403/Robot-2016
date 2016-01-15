/*
 * CougarEncoder.h
 *
 *  Created on: Jan 15, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_

#include <memory>
#include "WPILib.h"
#include "../../CougarDebug.h"

namespace cougar {

// It really feels like WPI didn't intend any of their classes to be inherited from
class CougarEncoder {
public:
	explicit CougarEncoder(uint32_t aChannel, uint32_t bChannel, bool reverseDirection = false, Encoder::EncodingType encodingType = Encoder::k4X);
	virtual ~CougarEncoder();

protected:
	std::shared_ptr<Encoder> encoder_;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_ */
