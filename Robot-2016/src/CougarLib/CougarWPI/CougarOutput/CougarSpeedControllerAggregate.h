/*
 * CougarSpeedControllerAggregate.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_
#define SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_

#include <memory>
#include "WPILib.h"
#include "CougarSpeedController.h"
#include "../../CougarDebug.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedControllerAggregate : public SpeedController {
public:
	CougarSpeedControllerAggregate(uint32_t port1, uint32_t port2,
			uint32_t PDPSlot1, uint32_t PDPSlot2, std::string name, bool inverted = false);
	CougarSpeedControllerAggregate(std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers,
			std::string name, bool inverted = false);
	explicit CougarSpeedControllerAggregate(std::shared_ptr<CougarSpeedControllerAggregate> controllers);
	explicit CougarSpeedControllerAggregate(const CougarSpeedControllerAggregate &controllers);
	virtual ~CougarSpeedControllerAggregate();

	virtual void SetInverted(bool inverted) override;
	virtual bool GetInverted() const override;

	virtual float Sign() const;
	virtual float GetCurrent() const;
	virtual void Set(float speed, uint8_t syncGroup = 0) override;
	virtual void StopMotor() override;
	virtual float Get() const override;
	virtual void Disable() override;
	virtual void PIDWrite(float output) override;
	virtual std::string GetName() const;
	virtual const char *GetCName() const;

protected:
	virtual std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> GetControllers() const;

	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers_;
	std::string name_;
	bool inverted_;

};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_ */
