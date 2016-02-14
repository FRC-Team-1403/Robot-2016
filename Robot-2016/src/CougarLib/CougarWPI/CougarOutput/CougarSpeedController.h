/*
 * CougarSpeedController.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */


#ifndef SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_
#define SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_

#include <memory>
#include "WPILib.h"
#include "../../CougarDebug.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedController : public SpeedController {
public:
	CougarSpeedController(uint32_t port, uint32_t pdpSlot, std::string name, bool inverted = false); // Creates a Victor by default
	CougarSpeedController(std::shared_ptr<SpeedController> controller, uint32_t pdpSlot, std::string name, bool inverted = false);
	explicit CougarSpeedController(std::shared_ptr<CougarSpeedController> controller);
	explicit CougarSpeedController(const CougarSpeedController &controller);
	virtual ~CougarSpeedController();

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
	virtual uint32_t GetPDPSlot() const;

protected:
	virtual std::shared_ptr<SpeedController> GetController() const;

	std::shared_ptr<SpeedController> controller_;
	std::string name_;
	uint32_t pdpSlot_;
	bool inverted_;
};

}

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_ */
