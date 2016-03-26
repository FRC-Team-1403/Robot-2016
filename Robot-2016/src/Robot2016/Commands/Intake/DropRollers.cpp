#include "DropRollers.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


DropRollers::DropRollers() :
	cougar::CougarCommand("DropRollers", Robot::oi->GetOperatorJoystick(), &cougar::CougarJoystick::GetButtonBothSticks)

{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void DropRollers::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DropRollers::Execute()
{
	Robot::intake->dropRollersAirCylinder();
}

// Make this return true when this Command no longer needs to run execute()
bool DropRollers::IsFinished()
{
	return Robot::intake->getRollersAirCylinderValue() == cougar::CougarDoubleSolenoid::kForward;
}

// Called once after isFinished returns true
void DropRollers::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropRollers::Interrupted()
{

}

void DropRollers::stopAll() {

}
