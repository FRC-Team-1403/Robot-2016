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
	Robot::shooter->goal_pos = 0; //Set it to the angle that the algorithm calculates.
}

// Called repeatedly when this Command is scheduled to run
void MoveShooter::Execute()
{
	Robot::shooter->calculate(Robot::shooter->shooterAngleMotor->GetEncPosition());
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooter::IsFinished()
{
	if (distanceToGo == 0) {
		return true;
	}
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
