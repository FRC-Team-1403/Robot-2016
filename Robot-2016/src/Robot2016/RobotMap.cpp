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

//intake
std::shared_ptr<cougar::CougarSpeedController> RobotMap::intakeRoller;
std::shared_ptr<DigitalInput> RobotMap::intakeBallSwitch;
std::shared_ptr<DoubleSolenoid> RobotMap::intakeAngleAirCylinder;
std::shared_ptr<DoubleSolenoid> RobotMap::intakeLiftAirCylinder;
std::shared_ptr<DigitalInput> RobotMap::intakeLimitSwitch;
//std::shared_ptr<Compressor> RobotMap::compressor;

void RobotMap::init(){
	LiveWindow *lw = LiveWindow::GetInstance();

	//drive train
	drive.reset(new cougar::CougarDrive(2, 3, 0, 1, 2, 3, 0, 1, "Drive")); //PWMs and PDPs
	driveTrainRightEncoder.reset(new Encoder(2, 3)); //Digital
	driveTrainLeftEncoder.reset(new Encoder(0, 1)); //Digital
	driveTrainGyro.reset(new cougar::CougarGyro(0)); //Analog
	driveTrainLeftEncoder->SetDistancePerPulse(1);
	driveTrainRightEncoder->SetDistancePerPulse(1);//23.8/85 to account for weirdness
	driveTrainAccelerometer.reset(new ADXL362(ADXL362::kRange_16G)); //SPI

	// TODO replace with actual ports
	//shooter
	shooterRollerTop.reset(new CANTalon(5)); //CAN
	shooterRollerBottom.reset(new CANTalon(4)); //CAN
	shooterAngleMotor.reset(new CANTalon(3)); //CAN

	//intake
	intakeRoller.reset(new cougar::CougarSpeedController(4, 102, "Intake Roller")); //PWM
	intakeBallSwitch.reset(new DigitalInput(4)); //Digital
	intakeAngleAirCylinder.reset(new DoubleSolenoid(5, 1)); //PWM
	intakeLiftAirCylinder.reset(new DoubleSolenoid(4, 2)); //PWM
	intakeLimitSwitch.reset(new DigitalInput(4));
	//compressor.reset(new Compressor()); //PWM

}
