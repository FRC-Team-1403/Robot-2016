#include "OI.h"
#include "Commands/MoveShooter.h"

OI::OI()
{
	cougar::CougarDebug::startMethod("OI::OI");
	this->driverJoy.reset(new cougar::CougarJoystick(0));
	this->operatorJoy.reset(new cougar::CougarJoystick(1));
	cougar::CougarDebug::endMethod("OI::OI");

	//operatorButtonY.reset(new cougar::CougarButton(driverJoy, 3));
	//operatorButtonY->WhenPressed(new MoveShooter());

}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
