#include "RobotMap.h"

//Drive Train
std::shared_ptr<cougar::CougarDrive> RobotMap::drive;
std::shared_ptr<cougar::CougarEncoder> RobotMap::driveTrainRightEncoder;
std::shared_ptr<cougar::CougarEncoder> RobotMap::driveTrainLeftEncoder;
std::shared_ptr<cougar::CougarGyro> RobotMap::driveTrainGyro;
std::shared_ptr<ADXL362> RobotMap::driveTrainAccelerometer;

//Shooter
std::shared_ptr<cougar::CougarCANTalon> RobotMap::shooterRollerTop;
std::shared_ptr<cougar::CougarCANTalon> RobotMap::shooterRollerBottom;
std::shared_ptr<cougar::CougarCANTalon> RobotMap::shooterAngleMotor;
std::shared_ptr<Servo> RobotMap::shooterCameraServo;

//Intake
std::shared_ptr<cougar::CougarSpeedController> RobotMap::intakeRoller;
std::shared_ptr<cougar::CougarDigitalInput> RobotMap::intakeBallSwitch;
std::shared_ptr<cougar::CougarDoubleSolenoid> RobotMap::intakeAngleAirCylinder;
std::shared_ptr<cougar::CougarSolenoid> RobotMap::intakeLiftAirCylinder;

void RobotMap::init(){
	LiveWindow *lw = LiveWindow::GetInstance();

/**********************************Drive Train**********************************/

	cougar::CougarDebug::debugPrinter("Starting Drive Train initialization");

	// Drive
	drive.reset(new cougar::CougarDrive(
				// Ports
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PORT_LEFT_1,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PORT_LEFT_2,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PORT_RIGHT_1,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PORT_RIGHT_2,

				// PDP Slots
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PDP_SLOT_LEFT_1,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PDP_SLOT_LEFT_2,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PDP_SLOT_RIGHT_1,
				cougar::CougarConstants::DRIVETRAIN_VICTOR_PDP_SLOT_RIGHT_2,

				// Name
				"Drive", true));

	cougar::CougarDebug::debugPrinter("Finished Drive initialization, beginning encoder init");

	// Left Encoder
	driveTrainLeftEncoder.reset(new cougar::CougarEncoder(
				cougar::CougarConstants::DRIVETRAIN_ENCODER_LEFT_ACHANNEL,
				cougar::CougarConstants::DRIVETRAIN_ENCODER_LEFT_BCHANNEL,
				"Drive Train Left Encoder"));
	driveTrainLeftEncoder->SetDistancePerPulse(cougar::CougarConstants::DRIVE_ENCODER_TICKS_PER_FOOT);

	// Right Encoder
	driveTrainRightEncoder.reset(new cougar::CougarEncoder(
				cougar::CougarConstants::DRIVETRAIN_ENCODER_RIGHT_ACHANNEL,
				cougar::CougarConstants::DRIVETRAIN_ENCODER_RIGHT_BCHANNEL,
				"Drive Train Right Encoder"));
	driveTrainRightEncoder->SetDistancePerPulse(cougar::CougarConstants::DRIVE_ENCODER_TICKS_PER_FOOT);

	cougar::CougarDebug::debugPrinter("Finished Drive initialization, finished encoder init");
	//std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

	cougar::CougarDebug::debugPrinter("starting gyro initialization");

	// Gyroscope
	driveTrainGyro.reset(new cougar::CougarGyro(
				cougar::CougarConstants::DRIVETRAIN_GYRO_CHANNEL, "Drive Train Gyro"));

	// SPI Accelerometer
	driveTrainAccelerometer.reset(new ADXL362(ADXL362::kRange_16G)); //SPI

	cougar::CougarDebug::debugPrinter("Finished Drive Train initialization");

/**********************************Shooter**********************************/

	cougar::CougarDebug::debugPrinter("Starting Shooter initialization");

	// Top Roller
	shooterRollerTop.reset(new cougar::CougarCANTalon(
				cougar::CougarConstants::SHOOTER_ROLLER_TOP_CANTALON_PORT,
				"Shooter Top Roller"));
	shooterRollerTop->SetFeedbackDevice(cougar::CougarCANTalon::QuadEncoder);
	shooterRollerTop->ConfigEncoderCodesPerRev(
				cougar::CougarConstants::SHOOTER_ROLLER_ENCODER_TICKS_PER_REV);
	shooterRollerTop->SetSensorDirection(
				cougar::CougarConstants::SHOOTER_ROLLER_TOP_CANTALON_REVERSE_SENSOR);
	//shooterRollerTop->SetControlMode(CANSpeedController::kSpeed);
	shooterRollerTop->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	// Bottom Roller
	shooterRollerBottom.reset(new cougar::CougarCANTalon(
				cougar::CougarConstants::SHOOTER_ROLLER_BOTTOM_CANTALON_PORT,
				"Shooter Bottom Roller"));
	shooterRollerBottom->SetFeedbackDevice(cougar::CougarCANTalon::QuadEncoder);
	shooterRollerBottom->ConfigEncoderCodesPerRev(
				cougar::CougarConstants::SHOOTER_ROLLER_ENCODER_TICKS_PER_REV);
	shooterRollerBottom->SetSensorDirection(
				cougar::CougarConstants::SHOOTER_ROLLER_BOTTOM_CANTALON_REVERSE_SENSOR);
	//shooterRollerBottom->SetControlMode(CANSpeedController::kSpeed);
	shooterRollerBottom->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	// Shooter Deck
	shooterAngleMotor.reset(new cougar::CougarCANTalon(
				cougar::CougarConstants::SHOOTER_DECK_ANGLE_CANTALON_PORT,
				"Shooter Angle Motor"));
	shooterAngleMotor->SetFeedbackDevice(cougar::CougarCANTalon::AnalogPot);
	shooterAngleMotor->SetSensorDirection(
				cougar::CougarConstants::SHOOTER_DECK_ANGLE_CANTALON_REVERSE_SENSOR);
	shooterAngleMotor->ConfigPotentiometerTurns(
				cougar::CougarConstants::SHOOTER_DECK_ANGLE_POTENTIOMETER_TURNS);
	/*shooterAngleMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SoftPositionLimits);
	shooterAngleMotor->ConfigForwardLimit(
				cougar::CougarConstants::SHOOTER_DECK_ANGLE_FORWARD_LIMIT);
	shooterAngleMotor->ConfigReverseLimit(
				cougar::CougarConstants::SHOOTER_DECK_ANGLE_REVERSE_LIMIT);*/
	//shooterAngleMotor->SetControlMode(CANSpeedController::kPosition);
	shooterAngleMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

	// Camera
	//TODO fix
	//shooterCameraServo.reset(new cougar::CougarSpeedController(std::make_shared<SpeedController>(new Servo(
	//			cougar::CougarConstants::SHOOTER_CAMERA_SERVO_PORT)), 1234, "Shooter Camera Servo"));

	shooterCameraServo.reset(new Servo(cougar::CougarConstants::SHOOTER_CAMERA_SERVO_PORT));
	cougar::CougarDebug::debugPrinter("Finished Shooter initialization");

/**********************************Intake**********************************/

	cougar::CougarDebug::debugPrinter("Starting Intake initialization");

	// Roller
	intakeRoller.reset(new cougar::CougarSpeedController(
				cougar::CougarConstants::INTAKE_ROLLER_VICTOR_PORT,
				cougar::CougarConstants::INTAKE_ROLLER_VICTOR_PDP_SLOT,
				"Intake Roller")); //PWM

	intakeAngleAirCylinder.reset(new cougar::CougarDoubleSolenoid(
				cougar::CougarConstants::INTAKE_ANGLE_DOUBLESOLENOID_FORWARD_CHANNEL,
				cougar::CougarConstants::INTAKE_ANGLE_DOUBLESOLENOID_REVERSE_CHANNEL,
				"Intake Roller Air Cylinder"));

	intakeLiftAirCylinder.reset(new cougar::CougarSolenoid(
				cougar::CougarConstants::INTAKE_TRIGGER_SOLENOID_CHANNEL,
				"Intake Trigger Air Cylinder"));

	intakeBallSwitch.reset(new cougar::CougarDigitalInput(
				cougar::CougarConstants::INTAKE_BALL_LIMIT_SWITCH_DIGITAL_INPUT_PORT,
				"Intake Ball Switch"));

	cougar::CougarDebug::debugPrinter("Finished Intake initialization");

}
