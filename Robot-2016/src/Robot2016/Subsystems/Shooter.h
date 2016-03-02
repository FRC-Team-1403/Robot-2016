#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include "../../CougarLib/CougarWPI/CougarOutput/CougarCANTalon.h"
#include "../../CougarLib/CougarConstants.h"
#include "../../CougarLib/CougarDebug.h"
#include <memory>

class Shooter: public Subsystem
{
public:

	enum AngleControlModes {
		BANG_BANG,
		PID_FEEDFORWARD
	};


	//projectile motion constants
	double x, y, d, vi, angle, k, s, h, a, e;
	//x = horizontal distance from shooter to goal
	//y = vertical distance from shooter to goal
	//d = diagonal distance from camera to goal
	//vi = initial velocity of ball
	//angle = angle the shooter must be set to
	//k = horizontal distance from shooter to camera
	//s = spin constant
	//h = height of shooter from ground
	//a = vertical acceleration of ball
	int i;
	//i = pseudo loop counter for CalculateAngle command

	bool autonomousMode; //true: default command is CalculateAngle, false: default command is AimWithJoystick

	Shooter();
	void InitDefaultCommand();

	void stop();
	double getPotentiometer();
	void setAngleMotor(double position);
	void setCameraServo(double position);
	void setTopRoller(double velocity);
	void setBottomRoller(double velocity);
	int getAngleMotorDistance();
	int getAngleMotorVelocity();
	int getTopRollerDistance();
	int getBottomRollerDistance();
	int getTopRollerVelocity();
	int getBottomRollerVelocity();

	//for projectile motion
	double calculateAngle();
	void setAngle(double value);
	double getAngle();
	double getDistance();

	bool getStopFlyWheels();

	std::shared_ptr<cougar::CougarCANTalon> bottomRoller;
	std::shared_ptr<cougar::CougarCANTalon> topRoller;
	std::shared_ptr<cougar::CougarCANTalon> angleMotor;
	std::shared_ptr<Servo> cameraServo;

};

#endif
