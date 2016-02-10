#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../../CougarLib/CougarWPI/CougarInput/CougarGyro.h"
#include <cmath>

class DriveTrain: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveTrain();
	void InitDefaultCommand();
	void drive();

	void setLeftRightPower(double leftPower, double rightPower) {
		driveTrainLeftTalon->Set(leftPower);
		driveTrainRightTalon->Set(rightPower);
	  }

	void stop() {
		setLeftRightPower(0, 0);
	}

	 double getRightEncoderDistance() {
		return driveTrainRightEncoder->GetDistance();
	  }

	 double getLeftEncoderDistance() {
	    return driveTrainLeftEncoder->GetDistance();
	  }

	 double getGyroAngleInRadians() {
		 return (driveTrainGyro->GetAngle() * M_PI) / 180.0;
	 }

	 void resetGyro() {
	     driveTrainGyro->Reset();
	   }

	 void resetEncoders() {
		 this->driveTrainLeftEncoder->Reset();
		 this->driveTrainRightEncoder->Reset();
	 }

	std::shared_ptr<CANTalon> driveTrainRightTalon;
	std::shared_ptr<CANTalon> driveTrainLeftTalon;
	std::shared_ptr<Encoder> driveTrainRightEncoder;
	std::shared_ptr<Encoder> driveTrainLeftEncoder;
	std::shared_ptr<cougar::CougarGyro> driveTrainGyro;
};

#endif
