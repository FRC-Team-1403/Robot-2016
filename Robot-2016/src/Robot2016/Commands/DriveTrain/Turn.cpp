#include "Turn.h"
#include "../../Robot.h"

Turn::Turn(double angle, std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("Turn", joy, true)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->angle = angle;
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void Turn::Initialize()
{
	Robot::driveTrain->resetGyro();
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute()
{
	Robot::driveTrain->setLeftRightPower(0.75, -0.75);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished()
{
	std::cout << "ANGLE: " << Robot::driveTrain->getGyroAngleInRadians() << "\n";
	return Robot::driveTrain->getGyroAngleInRadians() < this->angle;
}

// Called once after isFinished returns true
void Turn::End()
{
	stopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted()
{
	End();
}

void Turn::stopAll() {
	Robot::driveTrain->stop();
}
