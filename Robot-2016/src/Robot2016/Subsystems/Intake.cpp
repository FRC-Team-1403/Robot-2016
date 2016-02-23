#include "Intake.h"
#include "../RobotMap.h"
#include "../Commands/ControlIntake.h"

Intake::Intake() :
		Subsystem("ExampleSubsystem")
{
	this->roller = RobotMap::intakeRoller;
	this->ballSwitch = RobotMap::intakeBallSwitch;
	//this->ultrasonic = RobotMap::intakeUltrasonic;
	this->angleAirCyclinder = RobotMap::intakeAngleAirCyclinder;
	this->liftAirCyclinder = RobotMap::intakeLiftAirCyclinder;
	this->compressor = RobotMap::compressor;
	compressor->SetClosedLoopControl(true);
	compressor->Start();
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new ControlIntake());
}

void Intake::setAngleAirCyclinder(bool position) {
	angleAirCyclinder->Set(position);
}

void Intake::setLiftAirCyclinder(bool position) {
	liftAirCyclinder->Set(position);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
