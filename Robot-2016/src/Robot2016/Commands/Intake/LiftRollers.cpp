#include "LiftRollers.h"
#include "../../Robot.h"

LiftRollers::LiftRollers()
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
	return Robot::intake->getRollersAirCylinderValue() == DoubleSolenoid::kReverse;
}

// Called once after isFinished returns true
void LiftRollers::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftRollers::Interrupted()
{

}
