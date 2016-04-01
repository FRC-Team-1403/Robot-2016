#include "OI.h"
#include "Commands/Intake/DropRollers.h"
#include "Commands/Intake/LiftRollers.h"
#include "Commands/Intake/DropTrigger.h"
#include "Commands/Intake/LiftTrigger.h"
#include "Commands/Intake/RollersIn.h"
#include "Commands/Intake/RollersOut.h"
#include "Commands/Shooter/SetShooterDeckAngle.h"
#include "Commands/Shooter/PowerUpRollers.h"
#include "Commands/DoNothingAutonomous.h"

#include "Commands/IntakeBall.h"
#include "Commands/HighGoalBatter.h"
#include "Commands/Fire.h"
#include "Commands/LowBarPosition.h"
#include "Commands/LowGoal.h"
#include "Commands/TravelPosition.h"

OI::OI()
{
	cougar::CougarDebug::startMethod("OI::OI");
	this->driverJoy.reset(new cougar::CougarJoystick(0, false));
	this->operatorJoy.reset(new cougar::CougarJoystick(1, true));

	operatorButtonA.reset(new cougar::CougarButton(operatorJoy, 1));
	//operatorButtonA->WhenPressed(new DoNothingAutonomous());
	operatorButtonA->WhenPressed(new IntakeBall(this->operatorJoy));

	operatorButtonB.reset(new cougar::CougarButton(operatorJoy, 2));
	operatorButtonB->WhenPressed(new LowGoal(this->operatorJoy));
	//operatorButtonB->WhileHeld(new StopAllOperator());
	// TODO make a button to lift rollers

	operatorButtonX.reset(new cougar::CougarButton(operatorJoy, 3));
	operatorButtonX->WhenPressed(new HighGoalBatter(this->operatorJoy));

	operatorButtonY.reset(new cougar::CougarButton(operatorJoy, 4));
	operatorButtonY->WhenPressed(new Fire(this->operatorJoy));

	operatorButtonLB.reset(new cougar::CougarButton(operatorJoy, 5));
	operatorButtonLB->WhileHeld(new RollersOut(this->operatorJoy));
	//operatorButtonLB->WhenPressed(new SetShooterDeckAngle(0));

	operatorButtonRB.reset(new cougar::CougarButton(operatorJoy, 6));
	operatorButtonRB->WhileHeld(new RollersIn(this->operatorJoy));

	operatorButtonStart.reset(new cougar::CougarButton(operatorJoy, 8));
	operatorButtonStart->WhenPressed(new LowBarPosition(this->operatorJoy));

	operatorButtonBack.reset(new cougar::CougarButton(operatorJoy, 7));
	operatorButtonBack->WhenPressed(new TravelPosition(this->operatorJoy));

	cougar::CougarDebug::endMethod("OI::OI");
}

std::shared_ptr<cougar::CougarJoystick> OI::GetDriverJoystick() {
	//std::cout <<
	return driverJoy;
}

std::shared_ptr<cougar::CougarJoystick> OI::GetOperatorJoystick() {
	return operatorJoy;
}
