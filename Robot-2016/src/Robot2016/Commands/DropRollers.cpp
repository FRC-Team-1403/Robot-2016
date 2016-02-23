#include "DropRollers.h"
#include "../Robot.h"

DropRollers::DropRollers()
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
	Robot::intake->setLiftAirCylinder(DoubleSolenoid::kReverse);
}

// Make this return true when this Command no longer needs to run execute()
bool DropRollers::IsFinished()
{
	return Robot::intake->getLiftAirCylinderValue() == DoubleSolenoid::kReverse;
}

// Called once after isFinished returns true
void DropRollers::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropRollers::Interrupted()
{

}
