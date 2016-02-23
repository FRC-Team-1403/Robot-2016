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

	operatorButtonA.reset(new cougar::CougarButton(driverJoy, 1));
	operatorButtonA->WhenPressed(new DropRollers());

	operatorButtonB.reset(new cougar::CougarButton(driverJoy, 2));
	operatorButtonB->WhenPressed(new LiftRollers());

	operatorButtonX.reset(new cougar::CougarButton(driverJoy, 3));
	operatorButtonX->WhenPressed(new DropTrigger());

	operatorButtonY.reset(new cougar::CougarButton(driverJoy, 4));
	operatorButtonY->WhenPressed(new LiftTrigger());

	operatorButtonLB.reset(new cougar::CougarButton(driverJoy, 5));
	operatorButtonLB->WhileHeld(new RollersOut());

	operatorButtonRB.reset(new cougar::CougarButton(driverJoy, 6));
	operatorButtonRB->WhileHeld(new RollersIn());

	cougar::CougarDebug::endMethod("OI::OI");
}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
