#include "PowerUpRollers.h"
#include "../../Robot.h"

PowerUpRollers::PowerUpRollers(float topRollerPower, float bottomRollerPower)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter.get());
	this->topRollerPower_ = topRollerPower;
	this->bottomRollerPower_ = bottomRollerPower;
}

// Called just before this Command runs the first time
void PowerUpRollers::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PowerUpRollers::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool PowerUpRollers::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PowerUpRollers::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PowerUpRollers::Interrupted()
{

}
