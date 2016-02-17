#include "OI.h"

OI::OI()
{
	cougar::CougarDebug::startMethod("OI::OI");
	this->driverJoy.reset(new cougar::CougarJoystick(0));
	this->operatorJoy.reset(new cougar::CougarJoystick(1));
	cougar::CougarDebug::endMethod("OI::OI");
}


