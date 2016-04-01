#include "LowBarAutonomous_Drive.h"
#include "../../Robot.h"

LowBarAutonomous_Drive::LowBarAutonomous_Drive(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("LowBarAutonomous_Drive", joy)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::driveTrain.get());
	start_time = Timer::GetFPGATimestamp();
}

// Called just before this Command runs the first time
void LowBarAutonomous_Drive::Initialize()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_Drive::Initialize");
	Robot::driveTrain->resetEncoders();
	Robot::driveTrain->resetGyro();
	this->driveController.reset(new cougar::TrajectoryDriveController());
	driveController->loadProfile(Robot::lowBarPath->getLeftWheelTrajectory(), Robot::lowBarPath->getRightWheelTrajectory(), 1.0, Robot::driveTrain->getGyroAngleInRadians());
	driveController->enable();
	start_time = Timer::GetFPGATimestamp();
	cougar::CougarDebug::endMethod("LowBarAutonomous_Drive::Initialize");
}

void LowBarAutonomous_Drive::Execute()
{
    driveController->loadProfileNoReset(Robot::lowBarPath->getLeftWheelTrajectory(), Robot::lowBarPath->getRightWheelTrajectory());
	driveController->update();
}

// Make this return true when this Command no longer needs to run execute()
bool LowBarAutonomous_Drive::IsFinished()
{
	return driveController->onTarget() || Timer::GetFPGATimestamp() - start_time > 20;
}

// Called once after isFinished returns true
void LowBarAutonomous_Drive::End()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_Drive::End");
	stopAll();
	cougar::CougarDebug::endMethod("LowBarAutonomous_Drive::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowBarAutonomous_Drive::Interrupted()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_Drive::Interrupted");
	End();
	cougar::CougarDebug::endMethod("LowBarAutonomous_Drive::Interrupted");
}

void LowBarAutonomous_Drive::stopAll() {
	Robot::driveTrain->stop();
	driveController->disable();
}
