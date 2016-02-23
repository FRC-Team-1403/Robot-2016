#include "DropTrigger.h"
#include "../../Robot.h"

DropTrigger::DropTrigger()
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
	Robot::intake->setAngleAirCylinder(DoubleSolenoid::kReverse);
}

// Make this return true when this Command no longer needs to run execute()
bool DropTrigger::IsFinished()
{
	return Robot::intake->getAngleAirCylinderValue() == DoubleSolenoid::kReverse;
}

// Called once after isFinished returns true
void DropTrigger::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropTrigger::Interrupted()
{

}
