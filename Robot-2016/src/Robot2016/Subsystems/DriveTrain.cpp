#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/DriveWithJoystick.h"
#include "../Robot.h"

DriveTrain::DriveTrain() :
		Subsystem("ExampleSubsystem")
{
	this->driveT = RobotMap::drive;
	this->driveTrainLeftEncoder = RobotMap::driveTrainLeftEncoder;
	this->driveTrainRightEncoder = RobotMap::driveTrainRightEncoder;
	this->driveTrainGyro = RobotMap::driveTrainGyro;

}

void DriveTrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::drive() {
	this->driveT->ArcadeDrive(Robot::oi->GetJoystick(), cougar::CougarDrive::LEFT, false);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
