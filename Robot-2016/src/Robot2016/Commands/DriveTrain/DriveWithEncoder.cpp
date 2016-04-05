#include "DriveWithEncoder.h"
#include "../../Robot.h"

DriveWithEncoder::DriveWithEncoder(float distance, std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("DriveWithEncoder", joy, false)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::driveTrain.get());
	this->distance = distance;
}

// Called just before this Command runs the first time
void DriveWithEncoder::Initialize()
{
	Robot::driveTrain->resetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void DriveWithEncoder::Execute()
{
	if (distance > 1)
		Robot::driveTrain->setLeftRightPower(0.75, 0.78);
	else
		Robot::driveTrain->setLeftRightPower(-0.75, -0.78);

}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithEncoder::IsFinished()
{
	std::cout << "DISTANCE: " << std::abs(Robot::driveTrain->getDistance() * 2) << "\n";
	if (distance > 1)
		return std::abs(Robot::driveTrain->getDistance() * 2) > this->distance;
	else
		return (std::abs(Robot::driveTrain->getDistance() * 2) * -1) < this->distance;
}

// Called once after isFinished returns true
void DriveWithEncoder::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithEncoder::Interrupted()
{
	End();
}

void DriveWithEncoder::stopAll() {
	Robot::driveTrain->stop();
}
