#include "AutonomousDrive.h"
#include "../Robot.h"

AutonomousDrive::AutonomousDrive()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void AutonomousDrive::Initialize()
{
	std::cout << "Initializing autonomous drive\n";
	Robot::driveTrain->resetEncoders();
	Robot::driveTrain->resetGyro();
	this->driveController.reset(new cougar::TrajectoryDriveController());
	driveController->loadProfile(Robot::path->getLeftWheelTrajectory(), Robot::path->getRightWheelTrajectory(), 1.0, Robot::driveTrain->driveTrainGyro->GetAngle());
	driveController->enable();
	start_time = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDrive::Execute()
{
	driveController->update();
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDrive::IsFinished()
{
	return driveController->onTarget() || Timer::GetFPGATimestamp() - start_time > 20;
}

// Called once after isFinished returns true
void AutonomousDrive::End()
{
	std::cout << "Finished driving\n";
	Robot::driveTrain->stop();
	driveController->disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDrive::Interrupted()
{

}
