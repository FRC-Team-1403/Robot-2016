#include "OI.h"

OI::OI()
{
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "OI constructor running");
	joy.reset(new cougar::CougarJoystick(5));

}


