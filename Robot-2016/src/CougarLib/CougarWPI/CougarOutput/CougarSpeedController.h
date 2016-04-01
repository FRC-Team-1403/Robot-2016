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
#include "CougarDebug.h"
#include "CougarBase/Debuggable.h"
#include "CougarMacros.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedController : public SpeedController, public Debuggable {
public:
	CougarSpeedController(uint32_t port, uint32_t pdpSlot, std::string name, bool inverted = false); // Creates a Victor by default
	CougarSpeedController(std::shared_ptr<SpeedController> controller, uint32_t pdpSlot, std::string name, bool inverted = false);
	virtual ~CougarSpeedController();

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
	virtual uint32_t GetPDPSlot() const;

	virtual std::string toString() override;
	virtual std::string dumpState() override;
protected:
	virtual std::shared_ptr<SpeedController> GetController() const;

	std::shared_ptr<SpeedController> controller_;
	uint32_t port_;
	uint32_t pdpSlot_;
	bool inverted_;

	DISALLOW_COPY_AND_ASSIGN(CougarSpeedController)
};

}

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_ */
