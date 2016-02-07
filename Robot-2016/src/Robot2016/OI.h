#ifndef SRC_OI_H_
#define SRC_OI_H_

#include "WPILib.h"
#include <memory>
#include "../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"
#include "../CougarLib/CougarDebug.h"

class OI
{
private:
	std::shared_ptr<cougar::CougarJoystick> joy;

public:
	std::shared_ptr<cougar::CougarJoystick> GetJoystick() { return joy; }
	OI();

};

#endif
