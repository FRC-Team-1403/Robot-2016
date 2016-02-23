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

	operatorButtonLT.reset(new cougar::CougarButton(driverJoy, 4));
	operatorButtonLT->WhenPressed(new DropRollers());

	operatorButtonRT.reset(new cougar::CougarButton(driverJoy, 1));
	operatorButtonRT->WhenPressed(new LiftRollers());

	operatorButtonLB.reset(new cougar::CougarButton(driverJoy, 5));
	operatorButtonLB->WhenPressed(new DropTrigger());

	operatorButtonRB.reset(new cougar::CougarButton(driverJoy, 6));
	operatorButtonRB->WhenPressed(new LiftTrigger());

	operatorButtonA.reset(new cougar::CougarButton(driverJoy, 1));
	operatorButtonA->WhileHeld(new RollersOut());

	operatorButtonB.reset(new cougar::CougarButton(driverJoy, 2));
	operatorButtonB->WhileHeld(new RollersIn());






}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
