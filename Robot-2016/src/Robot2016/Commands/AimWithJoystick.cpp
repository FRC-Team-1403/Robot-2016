#include "MoveShooter.h"
#include "../Robot.h"

MoveShooter::MoveShooter()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void MoveShooter::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void MoveShooter::Execute()
{
	Robot::shooter->setAngleMotor(Robot::oi->operatorJoy->GetRawAxis(1));
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooter::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveShooter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooter::Interrupted()
{

}
