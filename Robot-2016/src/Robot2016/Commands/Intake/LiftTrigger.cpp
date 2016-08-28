#include "LiftTrigger.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


LiftTrigger::LiftTrigger(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("LiftTrigger", joy)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void LiftTrigger::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LiftTrigger::Execute()
{
	Robot::intake->liftTriggerAirCylinder();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftTrigger::IsFinished()
{
	return Robot::intake->getTriggerAirCylinderValue() == false;
}

// Called once after isFinished returns true
void LiftTrigger::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftTrigger::Interrupted()
{

}

void LiftTrigger::stopAll() {

}
