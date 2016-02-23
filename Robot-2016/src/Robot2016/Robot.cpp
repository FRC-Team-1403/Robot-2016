#include "Robot.h"
#include "RobotMap.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

int Robot::buffer;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<cougar::Path> Robot::lowBarPath;
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Intake> Robot::intake;
//std::shared_ptr<Camera> Robot::camera;

bool Robot::enabled;
bool Robot::autonomous;
bool Robot::teleop;
bool Robot::test;


void Robot::initModes() {
	setMode(false, false, false, false);
}

void Robot::setMode(bool e, bool a, bool t1, bool t2) {
	enabled = e;
	autonomous = a;
	teleop = t1;
	test = t2;
}

void Robot::update() {
	setMode(IsEnabled(), IsAutonomous(), IsOperatorControl(), IsTest());
}

bool Robot::isEnabled() {
	return enabled;
}

bool Robot::isAutonomous() {
	return autonomous;
}

bool Robot::isTeleop() {
	return teleop;
}

bool Robot::isTest() {
	return test;
}

void Robot::RobotInit()
{
	cougar::CougarDebug::init();
	cougar::CougarDebug::startMethod("Robot::RobotInit");
	buffer = 3;
	initModes();
	RobotMap::init();

	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization started");
	oi.reset(new OI());
	driveTrain.reset(new DriveTrain());
	shooter.reset(new Shooter());
	intake.reset(new Intake());
	//camera.reset(new Camera());
	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization finished");

	//intake->compressor->Start();

	cougar::CougarDebug::debugPrinter("SendableChooser initialization started");
	chooser = new SendableChooser();
	chooser->AddDefault("Default Auto", new LowBarAutonomous_Drive());
	SmartDashboard::PutData("Auto Modes", chooser);
	cougar::CougarDebug::debugPrinter("SendableChooser initialization finished");

	cougar::CougarDebug::debugPrinter("Motion mapping initialization started");
	std::shared_ptr<cougar::TrajectoryGenerator::Config> config(new cougar::TrajectoryGenerator::Config());
	//TODO find these values
	const double kWheelbaseWidth = 22.25/12;

	// Low Bar
	{
		config->dt = 0.02; // Periodic methods are called every 20 ms (I think), so dt is 0.02 seconds.
		config->max_acc = 30.0;
		config->max_jerk = 40.0;
		config->max_vel = 7.8;
		const std::string path_name = "LowBarPath";
		std::shared_ptr<cougar::WaypointSequence> p(new cougar::WaypointSequence(10));
		p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(0, 0, 0)));
		p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(2, 0, M_PI/12)));
		p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(4, 0, M_PI/6)));
		lowBarPath = cougar::PathGenerator::makePath(p, config, kWheelbaseWidth, path_name);
	}
	cougar::CougarDebug::debugPrinter("Motion mapping initialization finished");

	cougar::CougarDebug::endMethod("Robot::RobotInit");
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void Robot::DisabledInit()
{
	update();
	cougar::CougarDebug::startMethod("Robot::DisabledInit");
	std::cout << buffer << std::endl;
	buffer--;
	if (buffer == 0) {
		cougar::CougarDebug::end();
		buffer = 1;
		cougar::CougarDebug::init();
	}
	cougar::CougarDebug::endMethod("Robot::DisabledInit");
}

void Robot::DisabledPeriodic()
{
	Scheduler::GetInstance()->Run();
	update();
}

/**
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString code to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional commands to the chooser code above (like the commented example)
 * or additional comparisons to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit()
{
	update();
	cougar::CougarDebug::startMethod("Robot::AutonomousInit");
	/* std::string autoSelected = SmartDashboard::GetString("Auto Selector", "Default");
	if(autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	} else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	autonomousCommand.reset((Command *)chooser->GetSelected());

	if (autonomousCommand != NULL)
		autonomousCommand->Start();
	cougar::CougarDebug::endMethod("Robot::AutonomousInit");
}

void Robot::AutonomousPeriodic()
{
	Scheduler::GetInstance()->Run();
	update();

}

void Robot::TeleopInit()
{
	cougar::CougarDebug::startMethod("Robot::TeleopInit");
	update();
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();

	//drive train
	SmartDashboard::PutNumber("Drive Train Left Encoder", driveTrain->getLeftEncoderDistance());
	SmartDashboard::PutNumber("Drive Train Right Encoder", driveTrain->getRightEncoderDistance());
	SmartDashboard::PutNumber("Drive Train Gyro", driveTrain->getGyroAngleInRadians());
	//needs accelerometer

	//shooter
	//SmartDashboard::PutNumber("Shooter Angle", shooter->getPotentiometer());



	cougar::CougarDebug::endMethod("Robot::TInit");
}

void Robot::TeleopPeriodic()
{
	Scheduler::GetInstance()->Run();
	update();

	SmartDashboard::PutNumber("Joystick value", oi->GetDriverJoystick()->GetStickLeftAxisY());
	//SmartDashboard::PutNumber("Position", driveTrain->getDistance());
	SmartDashboard::PutNumber("Velocity", driveTrain->getVelocity());
	SmartDashboard::PutNumber("Acceleration", driveTrain->getAcceleration());
	SmartDashboard::PutNumber("Compressor", intake->compressor->GetPressureSwitchValue());
	SmartDashboard::PutNumber("Angle", driveTrain->getGyroAngleInRadians());
	SmartDashboard::PutNumber("Angular Velocity", driveTrain->getAngularVelocity());
	SmartDashboard::PutNumber("Drive Train Left Encoder", driveTrain->getLeftEncoderDistance());
	SmartDashboard::PutNumber("Drive Train Right Encoder", driveTrain->getRightEncoderDistance());
	SmartDashboard::PutNumber("POT", shooter->angleMotor->GetAnalogInRaw());

	//SmartDashboard::PutNumber("Goal Center X", shooter->getCameraCenterX());
	//SmartDashboard::PutNumber("Goal Center Y", shooter->getCameraCenterY());



	//SmartDashboard::PutNumber("Talon value", ((CANTalon&)exampleSubsystem->getMotor())->Get());
}

void Robot::TestPeriodic()
{
	LiveWindow::GetInstance()->Run();
	update();
}

START_ROBOT_CLASS(Robot)
