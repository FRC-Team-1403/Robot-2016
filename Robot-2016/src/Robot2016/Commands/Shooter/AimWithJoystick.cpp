#include "AimWithJoystick.h"
#include "../../Robot.h"

AimWithJoystick::AimWithJoystick()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void AimWithJoystick::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AimWithJoystick::Execute()
{
	Robot::shooter->setAngleMotor(.5 * Robot::oi->GetOperatorJoystick()->GetRawAxis(1));

	//Robot::shooter->setTopRoller(Robot::oi->GetOperatorJoystick()->GetStickRightAxisY());
	//Robot::shooter->setBottomRoller(Robot::oi->GetOperatorJoystick()->GetStickRightAxisY() * -1);

}

// Make this return true when this Command no longer needs to run execute()
bool AimWithJoystick::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AimWithJoystick::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimWithJoystick::Interrupted()
{

}
