/*
 * CougarSpeedController.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */


#ifndef SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_
#define SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_

#include "CougarIncludes.h"

namespace cougar {

class CougarSpeedController : public SpeedController {
public:
	explicit CougarSpeedController(SpeedController *controller, std::string name, uint32_t pdpSlot, bool inverted = false);
	explicit CougarSpeedController(SpeedController *controller, const char *name, uint32_t pdpSlot, bool inverted = false);
	virtual ~CougarSpeedController();

	virtual void SetInverted(bool inverted) override;
	virtual bool GetInverted() const override;

	virtual double Sign();
	virtual double GetCurrent();
	virtual void Set(float speed, uint8_t syncGroup = 0) override;
	virtual float Get() const override;
	virtual void Disable() override;
	virtual void PIDWrite(float output) override;
	virtual std::string GetName();
	virtual const char *GetCName();

protected:

	SpeedController *controller_;
	std::string name_;
	uint32_t pdpSlot_;
	bool inverted_;
};

}

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_ */
