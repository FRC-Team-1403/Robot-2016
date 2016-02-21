#ifndef SRC_OI_H_
#define SRC_OI_H_

#include "WPILib.h"
#include <memory>
#include "../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"
#include "../CougarLib/CougarDebug.h"

class OI
{
private:
	std::shared_ptr<cougar::CougarJoystick> driverJoy;
	std::shared_ptr<cougar::CougarJoystick> operatorJoy;

	std::shared_ptr<JoystickButton> operatorButtonY;

public:
	std::shared_ptr<cougar::CougarJoystick> GetDriverJoystick() { return this-> driverJoy; }
	std::shared_ptr<cougar::CougarJoystick> GetOperatorJoystick() { return this->operatorJoy; }
	OI();

};

#endif
