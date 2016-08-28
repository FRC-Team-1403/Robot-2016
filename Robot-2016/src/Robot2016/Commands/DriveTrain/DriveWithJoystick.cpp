#include "DriveWithJoystick.h"
#include "../../Robot.h"

DriveWithJoystick::DriveWithJoystick(std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("DriveWithJoystick", joy, true)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute()
{
	Robot::driveTrain->drive();
	if (Robot::oi->GetDriverJoystick()->GetButtonA()) {
		Robot::driveTrain->resetEncoders();
		Robot::driveTrain->resetGyro();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted()
{
	End();
}

void DriveWithJoystick::stopAll() {
	Robot::driveTrain->stop();
}
