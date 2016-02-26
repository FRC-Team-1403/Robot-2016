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

void RobotMap::init(){
	LiveWindow *lw = LiveWindow::GetInstance();

	//drive train
	drive.reset(new cougar::CougarDrive(2, 3, 0, 1, 2, 3, 0, 1, "Drive")); //PWMs and PDPs
	driveTrainRightEncoder.reset(new Encoder(2, 3)); //Digital
	driveTrainLeftEncoder.reset(new Encoder(0, 1)); //Digital
	driveTrainGyro.reset(new cougar::CougarGyro(0)); //Analog
	const float TICKS_PER_FOOT = 3.0/358.0;
	driveTrainLeftEncoder->SetDistancePerPulse(TICKS_PER_FOOT);
	driveTrainRightEncoder->SetDistancePerPulse(TICKS_PER_FOOT);
	driveTrainAccelerometer.reset(new ADXL362(ADXL362::kRange_16G)); //SPI

	//shooter

	// TODO fix

	shooterRollerTop.reset(new CANTalon(5));
	shooterRollerTop->SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterRollerTop->SetSensorDirection(false);
	//shooterRollerTop->SetControlMode(CANSpeedController::kSpeed);
	shooterRollerTop->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	shooterRollerBottom.reset(new CANTalon(4));
	shooterRollerBottom->SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterRollerBottom->SetSensorDirection(false);
	//shooterRollerBottom->SetControlMode(CANSpeedController::kSpeed);
	shooterRollerBottom->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	shooterAngleMotor.reset(new CANTalon(3));
	shooterAngleMotor->SetFeedbackDevice(CANTalon::AnalogPot);
	shooterAngleMotor->SetSensorDirection(false);
	shooterAngleMotor->ConfigPotentiometerTurns(1);
	//shooterAngleMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SoftPositionLimits);
	//shooterAngleMotor->ConfigForwardLimit(1);
	//shooterAngleMotor->ConfigReverseLimit(0);
	//shooterAngleMotor->SetControlMode(CANSpeedController::kPosition);
	shooterAngleMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

	//intake
	intakeRoller.reset(new cougar::CougarSpeedController(4, 102, "Intake Roller")); //PWM
	intakeAngleAirCylinder.reset(new DoubleSolenoid(5, 1)); //PWM
	intakeLiftAirCylinder.reset(new DoubleSolenoid(4, 2)); //PWM
	intakeBallSwitch.reset(new DigitalInput(4));
}
