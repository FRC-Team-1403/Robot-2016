#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/DriveTrainCommand.h"

DriveTrain::DriveTrain() :
		Subsystem("ExampleSubsystem")
{
	this->driveTrainLeftTalon = RobotMap::driveTrainLeftTalon;
	this->driveTrainRightTalon = RobotMap::driveTrainRightTalon;
	this->driveTrainLeftEncoder = RobotMap::driveTrainLeftEncoder;
	this->driveTrainRightEncoder = RobotMap::driveTrainRightEncoder;
	this->driveTrainGyro = RobotMap::driveTrainGyro;

}

void DriveTrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveTrainCommand());
}

void DriveTrain::drive() {

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
