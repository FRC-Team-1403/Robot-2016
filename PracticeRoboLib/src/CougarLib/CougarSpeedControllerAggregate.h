/*
 * CougarSpeedControllerAggregate.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_
#define SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_

#include "WPILib.h"
#include "CougarSpeedController.h"

namespace cougar {

class CougarSpeedControllerAggregate : SpeedController {
public:
	explicit CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, std::string name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, const char *name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, std::string name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, const char *name, bool inverted = false);
	virtual ~CougarSpeedControllerAggregate();

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
	std::vector<CougarSpeedController*> *controllers_;
	std::string name_;
	bool inverted_;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_ */
