#include "LowBarAutonomous_ReverseDrive.h"
#include "../../Robot.h"

LowBarAutonomous_ReverseDrive::LowBarAutonomous_ReverseDrive(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("LowBarAutonomous_ReverseDrive", joy)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::driveTrain.get());
	start_time = Timer::GetFPGATimestamp();
}

// Called just before this Command runs the first time
void LowBarAutonomous_ReverseDrive::Initialize()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_ReverseDrive::Initialize");
	Robot::driveTrain->resetEncoders();
	Robot::driveTrain->resetGyro();
	this->driveController.reset(new cougar::TrajectoryDriveController());
	driveController->loadProfile(Robot::lowBarReversePath->getLeftWheelTrajectory(), Robot::lowBarReversePath->getRightWheelTrajectory(), 1.0, Robot::driveTrain->getGyroAngleInRadians());
	driveController->enable();
	start_time = Timer::GetFPGATimestamp();
	cougar::CougarDebug::endMethod("LowBarAutonomous_ReverseDrive::Initialize");
}

void LowBarAutonomous_ReverseDrive::Execute()
{
   // driveController->loadProfileNoReset(Robot::lowBarPath->getLeftWheelTrajectory(), Robot::lowBarPath->getRightWheelTrajectory());
	driveController->update();
}

// Make this return true when this Command no longer needs to run execute()
bool LowBarAutonomous_ReverseDrive::IsFinished()
{
	return driveController->onTarget() || Timer::GetFPGATimestamp() - start_time > 20;
}

// Called once after isFinished returns true
void LowBarAutonomous_ReverseDrive::End()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_ReverseDrive::End");
	stopAll();
	cougar::CougarDebug::endMethod("LowBarAutonomous_ReverseDrive::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowBarAutonomous_ReverseDrive::Interrupted()
{
	cougar::CougarDebug::startMethod("LowBarAutonomous_ReverseDrive::Interrupted");
	End();
	cougar::CougarDebug::endMethod("LowBarAutonomous_ReverseDrive::Interrupted");
}

void LowBarAutonomous_ReverseDrive::stopAll() {
	Robot::driveTrain->stop();
	driveController->disable();
}
