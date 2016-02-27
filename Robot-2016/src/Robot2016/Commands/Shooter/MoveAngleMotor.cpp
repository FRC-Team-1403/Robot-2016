/*#include "MoveAngleMotor.h"
#include "../../Robot.h"

MoveAngleMotor::MoveAngleMotor()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void MoveAngleMotor::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void MoveAngleMotor::Execute()
{
	if (Robot::shooter->getPotentiometer() > Robot::shooter->getAngle()) {
		Robot::shooter->setAngleMotor(-1);
	}
	else if (Robot::shooter->getPotentiometer() < Robot::shooter->getAngle()) {
		Robot::shooter->setAngleMotor(1);
	}
	else {
		Robot::shooter->setAngleMotor(0);
	}
	//replace with 1D motion mapping code here later
}

// Make this return true when this Command no longer needs to run execute()
bool MoveAngleMotor::IsFinished()
{
	return (Robot::shooter->getPotentiometer() == Robot::shooter->getAngle());
}

// Called once after isFinished returns true
void MoveAngleMotor::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveAngleMotor::Interrupted()
{

}
*/

