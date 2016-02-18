#include "RobotMap.h"

std::shared_ptr<cougar::CougarDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::driveTrainRightEncoder;
std::shared_ptr<Encoder> RobotMap::driveTrainLeftEncoder;
std::shared_ptr<Gyro> RobotMap::driveTrainGyro;

std::shared_ptr<cougar::CougarSpeedController> RobotMap::shooterRollerTop;
std::shared_ptr<cougar::CougarSpeedController> RobotMap::shooterRollerBottom;

std::shared_ptr<cougar::CougarSpeedController> RobotMap::intakeRoller;


void RobotMap::init(){
//	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "RobotMap::init running");
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
	/*driveTrainRightTalon.reset(new Victor(0));
	driveTrainLeftTalon.reset(new Victor(1));
	*/
	drive.reset(new cougar::CougarDrive(0, 1, 12, 2, "Drive"));
	driveTrainRightEncoder.reset(new Encoder(0, 1));
	driveTrainLeftEncoder.reset(new Encoder(2, 3));
	driveTrainGyro.reset(new cougar::CougarGyro(0));
	driveTrainLeftEncoder->SetDistancePerPulse(1.0/170.0);
	driveTrainRightEncoder->SetDistancePerPulse(1.0/170.0);//23.8/85 to account for wierdness

	// TODO replace with actual ports

	shooterRollerTop.reset(new CANTalon(2), 100, "Top Shooter Roller");
	shooterRollerBottom.reset(new CANTalon(3), 101, "Bottom Shooter Roller");

	intakeRoller.reset(new Victor(24), 102, "Intake Roller");

}
