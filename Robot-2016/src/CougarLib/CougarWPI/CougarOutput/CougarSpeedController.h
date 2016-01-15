/*
 * CougarSpeedController.h
 *
 *  Created on: Jan 12, 2016
 *      Author: Thejas
 */


#ifndef SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_
#define SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_

#include "WPILib.h"
#include "../CougarDebug.h"
#include <vector>
#include <string>

namespace cougar {

class CougarSpeedController : public SpeedController {
public:
	explicit CougarSpeedController(SpeedController *controller, std::string name, uint32_t pdpSlot, bool inverted = false);
	explicit CougarSpeedController(SpeedController *controller, const char *name, uint32_t pdpSlot, bool inverted = false);
	explicit CougarSpeedController(CougarSpeedController *controller);
	explicit CougarSpeedController(CougarSpeedController &controller);
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

protected:

	class CougarSpeedControllerExtractor final {
	public:
		static SpeedController *extractSpeedController(CougarSpeedController *controller);
		static SpeedController *extractSpeedController(CougarSpeedController &controller);
		static std::string extractName(CougarSpeedController *controller);
		static std::string extractName(CougarSpeedController &controller);
		static uint32_t extractPDPSlot(CougarSpeedController *controller);
		static uint32_t extractPDPSlot(CougarSpeedController &controller);
	};
	friend CougarSpeedControllerExtractor;

	virtual SpeedController *getController() const;
	virtual std::string getName() const;
	virtual uint32_t getPDPSlot() const;

	SpeedController *controller_;
	std::string name_;
	uint32_t pdpSlot_;
	bool inverted_;
};

}

#endif /* SRC_COUGARLIB_COUGARSPEEDCONTROLLER_H_ */
