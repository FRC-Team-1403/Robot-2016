#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :
		Subsystem("ExampleSubsystem")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	this->ultrasonic = RobotMap::intakeUltrasonic;
	this->angleAirCyclinder = RobotMap::intakeAngleAirCyclinder;
	this->liftAirCyclinder = RobotMap::intakeLiftAirCyclinder;
	this->compressor = RobotMap::compressor;
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Intake::setAngleAirCyclinder(bool position) {
	angleAirCyclinder->Set(position);
}

void Intake::setLiftAirCyclinder(bool position) {
	liftAirCyclinder->Set(position);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
