#ifndef DriveTrain_H
#define DriveTrain_H

#include "WPILib.h"
#include <cmath>
#include "../../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"
#include "../../CougarLib/CougarWPI/CougarInput/CougarEncoder.h"
#include "../../CougarLib/CougarWPI/CougarInput/CougarGyro.h"
#include "../../CougarLib/CougarBase/CougarSubsystem.h"


class DriveTrain: public cougar::CougarSubsystem
{
private:
	std::shared_ptr<cougar::CougarDrive> driveT;
	std::shared_ptr<cougar::CougarEncoder> driveTrainRightEncoder;
	std::shared_ptr<cougar::CougarEncoder> driveTrainLeftEncoder;
	std::shared_ptr<cougar::CougarGyro> driveTrainGyro;

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
