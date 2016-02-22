#include "AimWithJoystick.h"
#include "../Robot.h"

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
	Robot::shooter->setAngleMotor(Robot::oi->GetOperatorJoystick()->GetRawAxis(1));

	if(Robot::oi->GetOperatorJoystick()->GetRawButton(0)) {
		Robot::shooter->setAngleMotor(.05 * Robot::oi->GetOperatorJoystick()->GetRawAxis(1));
	}
	else if(Robot::oi->GetOperatorJoystick()->GetRawButton(1)) {
		Robot::shooter->setAngleMotor(.1 * Robot::oi->GetOperatorJoystick()->GetRawAxis(1));
	}
	else if(Robot::oi->GetOperatorJoystick()->GetRawButton(2)) {
		Robot::shooter->setAngleMotor(.2 * Robot::oi->GetOperatorJoystick()->GetRawAxis(1));
	}
	else if(Robot::oi->GetOperatorJoystick()->GetRawButton(3)) {
		Robot::shooter->setAngleMotor(.5 * Robot::oi->GetOperatorJoystick()->GetRawAxis(1));
	}
	else {
		Robot::shooter->setAngleMotor(Robot::oi->GetOperatorJoystick()->GetRawAxis(1));
	}

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
