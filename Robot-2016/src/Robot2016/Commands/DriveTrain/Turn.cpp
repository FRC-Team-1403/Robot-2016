#include "Turn.h"
#include "../../Robot.h"

Turn::Turn(double angle, std::shared_ptr<cougar::CougarJoystick> joy) :
	cougar::CougarCommand("Turn", joy, false)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->angleDelta = angle;
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void Turn::Initialize()
{
	initAngle = Robot::driveTrain->getGyroAngleInRadians();
	setpointAngle = initAngle + angleDelta;
	error = setpointAngle;
	errorSum = 0;
	lastError = setpointAngle;
	lastTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute()
{

	error = setpointAngle - Robot::driveTrain->getGyroAngleInRadians();

		//proportional
		powerP = kP * error;

		//integral
		errorSum += error;
		powerI = kI * errorSum;

		//derivative
		powerD = kD * ((error - lastError) / (Timer::GetFPGATimestamp() - lastTime));
		lastTime = Timer::GetFPGATimestamp();

		power = powerP + powerI + powerD;

		cougar::CougarDebug::debugPrinter("Error: %f", error);
		cougar::CougarDebug::debugPrinter("Power: %f", power);
		cougar::CougarDebug::debugPrinter("PowerP: %f", powerP);
		cougar::CougarDebug::debugPrinter("PowerI: %f", powerI);
		cougar::CougarDebug::debugPrinter("PowerD: %f", powerD);

		Robot::driveTrain->setLeftRightPower(-power,power);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished()
{
	cougar::CougarDebug::debugPrinter("Angle: %f", Robot::driveTrain->getGyroAngleInRadians());
	return std::abs(Robot::driveTrain->getGyroAngleInRadians() - this->setpointAngle) < 0.01;
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
