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
#include "../CougarDebug.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedControllerAggregate : SpeedController {
public:
	explicit CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, std::string name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(std::vector<CougarSpeedController*> *controllers, const char *name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, std::string name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(CougarSpeedController *controllers, uint32_t count, const char *name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(CougarSpeedControllerAggregate *controllers);
	explicit CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers);
	virtual ~CougarSpeedControllerAggregate();

	virtual void SetInverted(bool inverted) override;
	virtual bool GetInverted() const override;

	virtual float Sign() const;
	virtual float GetCurrent() const;
	virtual void Set(float speed, uint8_t syncGroup = 0) override;
	virtual float Get() const override;
	virtual void Disable() override;
	virtual void PIDWrite(float output) override;
	virtual std::string GetName() const;
	virtual const char *GetCName() const;

protected:

	class CougarSpeedControllerAggregateExtractor final {
	public:
		static std::vector<CougarSpeedController*> *extractControllers(CougarSpeedControllerAggregate *controllers);
		static std::vector<CougarSpeedController*> *extractControllers(const CougarSpeedControllerAggregate &controllers);
	};
	friend CougarSpeedControllerAggregateExtractor;

	virtual std::vector<CougarSpeedController*> *getControllers() const;

	std::vector<CougarSpeedController*> *controllers_;
	std::string name_;
	bool inverted_;
	bool shouldDelete_;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_ */
