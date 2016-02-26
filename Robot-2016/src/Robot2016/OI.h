#ifndef SRC_OI_H_
#define SRC_OI_H_

#include "WPILib.h"
#include <memory>
#include "../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"
#include "../CougarLib/CougarWPI/CougarHID/CougarButton.h"
#include "../CougarLib/CougarDebug.h"

class OI
{
private:
	std::shared_ptr<cougar::CougarJoystick> driverJoy;
	std::shared_ptr<cougar::CougarJoystick> operatorJoy;

	std::shared_ptr<cougar::CougarButton> operatorButtonA;
	std::shared_ptr<cougar::CougarButton> operatorButtonB;
	std::shared_ptr<cougar::CougarButton> operatorButtonX;
	std::shared_ptr<cougar::CougarButton> operatorButtonY;
	std::shared_ptr<cougar::CougarButton> operatorButtonLB;
	std::shared_ptr<cougar::CougarButton> operatorButtonRB;
	std::shared_ptr<cougar::CougarButton> operatorButtonStart;
	std::shared_ptr<cougar::CougarButton> operatorButtonBack;

public:
	std::shared_ptr<cougar::CougarJoystick> GetDriverJoystick();
	std::shared_ptr<cougar::CougarJoystick> GetOperatorJoystick();
	OI();

};

#endif
