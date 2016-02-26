#include <Robot2016/Commands/StopAllOperator.h>
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
	this->operatorJoy.reset(new cougar::CougarJoystick(1, true));

	operatorButtonA.reset(new cougar::CougarButton(operatorJoy, 1));
	operatorButtonA->WhenPressed(new DropRollers());

	operatorButtonB.reset(new cougar::CougarButton(operatorJoy, 2));
	operatorButtonB->WhenPressed(new StopAll());
	// TODO make a button to lift rollers

	operatorButtonX.reset(new cougar::CougarButton(operatorJoy, 3));
	operatorButtonX->WhenPressed(new DropTrigger());

	operatorButtonY.reset(new cougar::CougarButton(operatorJoy, 4));
	operatorButtonY->WhenPressed(new LiftTrigger());

	operatorButtonLB.reset(new cougar::CougarButton(operatorJoy, 5));
	operatorButtonLB->WhileHeld(new RollersOut());

	operatorButtonRB.reset(new cougar::CougarButton(operatorJoy, 6));
	operatorButtonRB->WhileHeld(new RollersIn());

	cougar::CougarDebug::endMethod("OI::OI");
}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
