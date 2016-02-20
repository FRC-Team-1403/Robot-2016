#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		Subsystem("ExampleSubsystem")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	this->ultrasonic = RobotMap::intakeUltrasonic;
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
