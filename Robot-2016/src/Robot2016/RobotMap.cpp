#include "RobotMap.h"

std::shared_ptr<CANTalon> RobotMap::driveTrainRightTalon;
std::shared_ptr<CANTalon> RobotMap::driveTrainLeftTalon;
std::shared_ptr<Encoder> RobotMap::driveTrainRightEncoder;
std::shared_ptr<Encoder> RobotMap::driveTrainLeftEncoder;
std::shared_ptr<cougar::CougarGyro> RobotMap::driveTrainGyro;


void RobotMap::init(){
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "RobotMap::init running");
	// Couldn't get smart pointers working :(
	// BTW I don't actually like smart pointers
	// I'm just using them because they're less painful sometimes
	LiveWindow *lw = LiveWindow::GetInstance();

	/*
	std::shared_ptr<SpeedController> asdf(new CANTalon(1));
	cougar::CougarSpeedController *asdf2 = new cougar::CougarSpeedController(asdf, std::string("Motor"), 1);
	std::shared_ptr<cougar::CougarSpeedController> asdf3(asdf2);
	std::vector<std::shared_ptr<cougar::CougarSpeedController>> *asdf4 = new std::vector<std::shared_ptr<cougar::CougarSpeedController>>();
	asdf4->push_back(asdf3);
	std::shared_ptr<std::vector<std::shared_ptr<cougar::CougarSpeedController>>> asdf5(asdf4);
	//std::shared_ptr<cougar::CougarSpeedControllerAggregate> asdf5(asdf4, "pls work");

	//motor.reset(new cougar::CougarSpeedControllerAggregate(asdf5, "pls work"));

	 */
	driveTrainRightTalon.reset(new CANTalon(1));
	driveTrainLeftTalon.reset(new CANTalon(2));
	drive.reset(new cougar::CougarDrive(driveTrainRightTalon, driveTrainLeftTalon, "Drive"));
	driveTrainRightEncoder.reset(new Encoder(1, 2));
	driveTrainLeftEncoder.reset(new Encoder(3, 4));
	driveTrainGyro.reset(new cougar::CougarGyro(0));
	//motor.reset(new CANTalon(1));
}
