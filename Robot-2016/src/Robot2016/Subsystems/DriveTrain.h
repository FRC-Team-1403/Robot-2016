#ifndef DriveTrain_H
#define DriveTrain_H

//#include "Commands/Subsystem.h"
#include "WPILib.h"
//#include "../../CougarLib/CougarWPI/CougarInput/CougarGyro.h"
#include <cmath>
#include "../../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

class DriveTrain: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<cougar::CougarDrive> driveT;
	std::shared_ptr<Encoder> driveTrainRightEncoder;
	std::shared_ptr<Encoder> driveTrainLeftEncoder;
	std::shared_ptr<Gyro> driveTrainGyro;

	double time;
	double distance;
	double vel;
	double acc;
	double angle;

public:
	DriveTrain();
	void InitDefaultCommand();
	void drive();

	double getDistance();
	double getVelocity();
	double getAcceleration();
	double getJerk();
	double getAngularVelocity();
	void setLeftRightPower(double leftPower, double rightPower);
	void stop();
	double getRightEncoderDistance();
	double getLeftEncoderDistance();
	double getGyroAngleInRadians();
	void resetGyro();
	void resetEncoders();
};

#endif
