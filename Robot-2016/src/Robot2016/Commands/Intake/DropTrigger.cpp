#include "DropTrigger.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


DropTrigger::DropTrigger() :
	cougar::CougarCommand("DropTrigger", Robot::oi->GetOperatorJoystick(), &cougar::CougarJoystick::GetButtonBothSticks)

{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void DropTrigger::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DropTrigger::Execute()
{
	Robot::intake->dropTriggerAirCylinder();
}

// Make this return true when this Command no longer needs to run execute()
bool DropTrigger::IsFinished()
{
	return Robot::intake->getTriggerAirCylinderValue() == true;
}

// Called once after isFinished returns true
void DropTrigger::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropTrigger::Interrupted()
{

}

void DropTrigger::stopAll() {

}
