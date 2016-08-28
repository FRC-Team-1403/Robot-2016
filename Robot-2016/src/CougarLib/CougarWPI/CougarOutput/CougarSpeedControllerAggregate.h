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
#include "CougarDebug.h"
#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedControllerAggregate : public SpeedController, public Debuggable {
public:
	CougarSpeedControllerAggregate(uint32_t port1, uint32_t port2,
			uint32_t PDPSlot1, uint32_t PDPSlot2, std::string name, bool inverted = false);
	CougarSpeedControllerAggregate(std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers,
			std::string name, bool inverted = false);
	virtual ~CougarSpeedControllerAggregate();

	virtual void SetInverted(bool inverted) override;
	virtual bool GetInverted() const override;

	// TODO implement getting current draw

	virtual float Sign() const;
	virtual void Set(float speed, uint8_t syncGroup = 0) override;
	virtual void StopMotor() override;
	virtual float Get() const override;
	virtual void Disable() override;
	virtual void PIDWrite(float output) override;
	virtual std::string GetName() const;
	virtual const char *GetCName() const;

	virtual std::string toString() override;
	virtual std::string dumpState() override;

protected:
	virtual std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> GetControllers() const;

	std::shared_ptr<std::vector<std::shared_ptr<CougarSpeedController>>> controllers_;
	bool inverted_;

	DISALLOW_COPY_AND_ASSIGN(CougarSpeedControllerAggregate)
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLERAGGREGATE_H_ */
