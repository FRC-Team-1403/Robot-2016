#include "LiftTrigger.h"
#include "../Robot.h"

LiftTrigger::LiftTrigger()
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
	Robot::intake->setAngleAirCylinder(DoubleSolenoid::kForward);
}

// Make this return true when this Command no longer needs to run execute()
bool LiftTrigger::IsFinished()
{
	return Robot::intake->getAngleAirCylinderValue() == DoubleSolenoid::kForward;
}

// Called once after isFinished returns true
void LiftTrigger::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftTrigger::Interrupted()
{

}
