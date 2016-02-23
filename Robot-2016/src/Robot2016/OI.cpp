#include "OI.h"
#include "Commands/Intake/DropRollers.h"
#include "Commands/Intake/LiftRollers.h"
#include "Commands/Intake/DropTrigger.h"
#include "Commands/Intake/LiftTrigger.h"
#include "Commands/Intake/RollersIn.h"
#include "Commands/Intake/RollersOut.h"


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
