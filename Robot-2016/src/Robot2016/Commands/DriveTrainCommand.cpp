#include "DriveTrainCommand.h"

DriveTrainCommand::DriveTrainCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void DriveTrainCommand::Initialize()
{
	//Robot::driveTrain->resetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void DriveTrainCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveTrainCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveTrainCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTrainCommand::Interrupted()
{

}
