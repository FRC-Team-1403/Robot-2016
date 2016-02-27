#include "CalculateAngle.h"
#include "../../Robot.h"
#include "CougarLib/CougarConstants.h"

CalculateAngle::CalculateAngle()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter.get());
	isFinished = false;
}

// Called just before this Command runs the first time
void CalculateAngle::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CalculateAngle::Execute()
{
	//Robot::shooter->setAngle(Robot::shooter->calculateAngle());
	/*double i = Robot::shooter->getI();
	double e = cougar::CougarConstants::ACCEPTABLE_ERROR_IN_ANGLE;
	//double d = Robot::shooter->getDistance();
	double y = cougar::CougarConstants::VERTICAL_DISTANCE_FROM_TOWER;
	//double x = sqrt(d*d-y*y)+cougar::CougarConstants::DISTANCE_FROM_CAMERA;
	double vi = cougar::CougarConstants::INITIAL_VELOCITY;
	double a = cougar::CougarConstants::VERTICAL_ACCELERATION;*/

	/*Robot::shooter->setI(i+1);

	if((y-e < x*tan(i)+(2*x*x)/(vi*vi*cos(i)*cos(i))) && (y+e > x*tan(i)+(a*x*x)/(2*vi*vi*cos(i)*cos(i)))) {
		//Robot::shooter->setAngle(i-90);
		Robot::shooter->setI(0);
		isFinished = true;
	}*/
}

// Make this return true when this Command no longer needs to run execute()
bool CalculateAngle::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void CalculateAngle::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalculateAngle::Interrupted()
{

}
