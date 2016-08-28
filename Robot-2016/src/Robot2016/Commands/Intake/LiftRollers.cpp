#include "LiftRollers.h"
#include "../../Robot.h"
#include "../../../CougarLib/CougarWPI/CougarHID/CougarJoystick.h"


LiftRollers::LiftRollers(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("LiftRollers", joy)

{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void LiftRollers::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LiftRollers::Execute()
{
	Robot::intake->liftRollersAirCylinder();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftRollers::IsFinished()
{
	return Robot::intake->getRollersAirCylinderValue() == cougar::CougarDoubleSolenoid::kReverse;
}

// Called once after isFinished returns true
void LiftRollers::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftRollers::Interrupted()
{

}

void LiftRollers::stopAll() {

}
