/*
 * CougarEncoder.h
 *
 *  Created on: Mar 10, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_

#include "WPILib.h"
#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"

namespace cougar {

class CougarEncoder : public Encoder, public Debuggable {
public:
	CougarEncoder(uint32_t aChannel, uint32_t bChannel, std::string name, bool reverseDirection = false,
	          EncodingType encodingType = k4X);
	CougarEncoder(std::shared_ptr<DigitalSource> aSource,
			std::shared_ptr<DigitalSource> bSource, std::string name,
			bool reverseDirection = false, EncodingType encodingType = k4X);
	CougarEncoder(DigitalSource *aSource, DigitalSource *bSource, std::string name,
			bool reverseDirection = false, EncodingType encodingType = k4X);
	CougarEncoder(DigitalSource &aSource, DigitalSource &bSource, std::string name,
			bool reverseDirection = false, EncodingType encodingType = k4X);
	virtual ~CougarEncoder();

	virtual std::string toString() override;
	virtual std::string dumpState() override;

	DISALLOW_COPY_AND_ASSIGN(CougarEncoder)

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARENCODER_H_ */
