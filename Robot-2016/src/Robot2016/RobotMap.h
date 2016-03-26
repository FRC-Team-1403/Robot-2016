#ifndef SRC_ROBOTMAP_H_
#define SRC_ROBOTMAP_H_

#include <memory>
#include "WPILib.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarCANTalon.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarSpeedControllerAggregate.h"
#include "../CougarLib/CougarDebug.h"
#include "../CougarLib/CougarWPI/CougarInput/CougarGyro.h"
#include "../CougarLib/CougarWPI/CougarInput/CougarEncoder.h"
#include "../CougarLib/CougarWPI/CougarInput/CougarDigitalInput.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarSolenoid.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDoubleSolenoid.h"
#include "../CougarLib/CougarConstants.h"

class RobotMap {
public:
	static void init();

	//drive train
	static std::shared_ptr<cougar::CougarDrive> drive;
	static std::shared_ptr<cougar::CougarEncoder> driveTrainRightEncoder;
	static std::shared_ptr<cougar::CougarEncoder> driveTrainLeftEncoder;
	static std::shared_ptr<cougar::CougarGyro> driveTrainGyro;
	static std::shared_ptr<ADXL362> driveTrainAccelerometer;

	//shooter
	static std::shared_ptr<cougar::CougarCANTalon> shooterRollerTop;
	static std::shared_ptr<cougar::CougarCANTalon> shooterRollerBottom;
	static std::shared_ptr<cougar::CougarCANTalon> shooterAngleMotor;
	static std::shared_ptr<Servo> shooterCameraServo;

	//intake
	static std::shared_ptr<cougar::CougarSpeedController> intakeRoller;
	static std::shared_ptr<cougar::CougarDigitalInput> intakeBallSwitch;
	static std::shared_ptr<cougar::CougarDoubleSolenoid> intakeAngleAirCylinder;
	static std::shared_ptr<cougar::CougarSolenoid> intakeLiftAirCylinder;
};

#endif
