#include "RobotMap.h"

//drive train
std::shared_ptr<cougar::CougarDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::driveTrainRightEncoder;
std::shared_ptr<Encoder> RobotMap::driveTrainLeftEncoder;
std::shared_ptr<Gyro> RobotMap::driveTrainGyro;
std::shared_ptr<ADXL362> RobotMap::driveTrainAccelerometer;

//shooter
std::shared_ptr<CANTalon> RobotMap::shooterRollerTop;
std::shared_ptr<CANTalon> RobotMap::shooterRollerBottom;
std::shared_ptr<CANTalon> RobotMap::shooterAngleMotor;
//std::shared_ptr<AnalogPotentiometer> RobotMap::shooterPotentiometer;

//as cougar speed controllers
//std::shared_ptr<cougar::CougarSpeedController> RobotMap::shooterRollerTop;
//std::shared_ptr<cougar::CougarSpeedController> RobotMap::shooterRollerBottom;

//intake
std::shared_ptr<cougar::CougarSpeedController> RobotMap::intakeRoller;
std::shared_ptr<DigitalInput> RobotMap::intakeBallSwitch;
std::shared_ptr<Ultrasonic> RobotMap::intakeUltrasonic;


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
	//drive train
	drive.reset(new cougar::CougarDrive(0, 1, 12, 2, "Drive"));
	driveTrainRightEncoder.reset(new Encoder(0, 1));
	driveTrainLeftEncoder.reset(new Encoder(2, 3));
	driveTrainGyro.reset(new cougar::CougarGyro(0));
	driveTrainLeftEncoder->SetDistancePerPulse(1.0/170.0);
	driveTrainRightEncoder->SetDistancePerPulse(1.0/170.0);//23.8/85 to account for weirdness
	driveTrainAccelerometer.reset(new ADXL362(ADXL362::kRange_16G));

	// TODO replace with actual ports
	//shooter
	shooterRollerTop.reset(new CANTalon(2));
	shooterRollerBottom.reset(new CANTalon(3));
	shooterAngleMotor.reset(new CANTalon(4));
	//shooterPotentiometer.reset(new AnalogPotentiometer(2));

	//these are with cougar speed controllers
	//shooterRollerTop.reset(new cougar::CougarSpeedController(std::shared_ptr<SpeedController>(new CANTalon(2)), 100, "Top Shooter Roller"));
	//shooterRollerBottom.reset(new cougar::CougarSpeedController(std::shared_ptr<SpeedController>(new CANTalon(3)), 101, "Bottom Shooter Roller"));

	//intake
	intakeRoller.reset(new cougar::CougarSpeedController(24, 102, "Intake Roller"));
	intakeBallSwitch.reset(new DigitalInput(1));
	intakeUltrasonic.reset(new Ultrasonic(7, 8, Ultrasonic::kInches));

}
