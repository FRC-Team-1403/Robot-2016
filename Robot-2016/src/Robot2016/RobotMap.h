#ifndef SRC_ROBOTMAP_H_
#define SRC_ROBOTMAP_H_

#include <memory>
#include "WPILib.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarSpeedController.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarSpeedControllerAggregate.h"
#include "../CougarLib/CougarDebug.h"
#include "../CougarLib/CougarWPI/CougarInput/CougarGyro.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

class RobotMap {
public:
	static void init();

	static std::shared_ptr<cougar::CougarDrive> drive;
	static std::shared_ptr<Encoder> driveTrainRightEncoder;
	static std::shared_ptr<Encoder> driveTrainLeftEncoder;
	static std::shared_ptr<Gyro> driveTrainGyro;
};

#endif
