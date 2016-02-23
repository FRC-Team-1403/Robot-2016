#include "OI.h"
#include "Commands/MoveShooter.h"
#include "Commands/DropRollers.h"
#include "Commands/LiftRollers.h"
#include "Commands/DropTrigger.h"
#include "Commands/LiftTrigger.h"
#include "Commands/RollersIn.h"
#include "Commands/RollersOut.h"


OI::OI()
{
	cougar::CougarDebug::startMethod("OI::OI");
	this->driverJoy.reset(new cougar::CougarJoystick(0));
	this->operatorJoy.reset(new cougar::CougarJoystick(1));
	cougar::CougarDebug::endMethod("OI::OI");

	operatorButtonY.reset(new cougar::CougarButton(driverJoy, 4));
	operatorButtonY->WhenPressed(new DropRollers());

	operatorButtonA.reset(new cougar::CougarButton(driverJoy, 1));
	operatorButtonA->WhenPressed(new LiftRollers());
	operatorButtonLB.reset(new cougar::CougarButton(driverJoy, 5));
	operatorButtonLB->WhenPressed(new DropTrigger());

	operatorButtonRB.reset(new cougar::CougarButton(driverJoy, 6));
	operatorButtonRB->WhenPressed(new LiftTrigger());

	operatorButtonB.reset(new cougar::CougarButton(driverJoy, 2));
	operatorButtonB->WhileHeld(new RollersIn());

	operatorButtonX.reset(new cougar::CougarButton(driverJoy, 3));
	operatorButtonX->WhileHeld(new RollersOut());





}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
