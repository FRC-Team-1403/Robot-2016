#include "Robot.h"
#include "RobotMap.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

int Robot::buffer;
std::shared_ptr<OI> Robot::oi;
std::shared_ptr<cougar::Path> Robot::lowBarPath;
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Intake> Robot::intake;

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
	buffer = 3;
	cougar::CougarDebug::init();
	cougar::CougarDebug::startMethod("Robot::RobotInit");
	initModes();
	RobotMap::init();

	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization started");
	oi.reset(new OI());
	driveTrain.reset(new DriveTrain());
	shooter.reset(new Shooter());
	intake.reset(new Intake());
	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization finished");


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

void Robot::AutonomousInit()
{
	update();
	cougar::CougarDebug::startMethod("Robot::AutonomousInit");

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

	cougar::CougarDebug::endMethod("Robot::TeleopInit");
}

void Robot::TeleopPeriodic()
{
	Scheduler::GetInstance()->Run();
	update();

	SmartDashboard::PutNumber("Joystick value", oi->GetDriverJoystick()->GetStickLeftAxisY());
	//SmartDashboard::PutNumber("Position", driveTrain->getDistance());
	//SmartDashboard::PutNumber("Velocity", driveTrain->getVelocity());
	//SmartDashboard::PutNumber("Acceleration", driveTrain->getAcceleration());
	SmartDashboard::PutNumber("Compressor", intake->getPressureSwitchValue());
	SmartDashboard::PutNumber("Angle", driveTrain->getGyroAngleInRadians());
	SmartDashboard::PutNumber("Angular Velocity", driveTrain->getAngularVelocity());
	SmartDashboard::PutNumber("Drive Train Left Encoder", driveTrain->getLeftEncoderDistance());
	SmartDashboard::PutNumber("Drive Train Right Encoder", driveTrain->getRightEncoderDistance());
	SmartDashboard::PutNumber("POT distance", shooter->getAngleMotorDistance());
	SmartDashboard::PutNumber("POT velocity", shooter->getAngleMotorVelocity());
	SmartDashboard::PutNumber("Top Roller position", shooter->getTopRollerDistance());
	SmartDashboard::PutNumber("Bottom Roller position", shooter->getTopRollerDistance());
	SmartDashboard::PutNumber("Top Roller velocity", shooter->getTopRollerVelocity());
	SmartDashboard::PutNumber("Bottom Roller velocity", shooter->getTopRollerVelocity());
	SmartDashboard::PutNumber("Intake limit switch", intake->getLimitSwitchValue());
	SmartDashboard::PutNumber("Roller Solenoid", intake->getRollersAirCylinderValue());
	SmartDashboard::PutNumber("Trigger Solenoid", intake->getTriggerAirCylinderValue());
}

void Robot::TestPeriodic()
{
	LiveWindow::GetInstance()->Run();
	update();
}

START_ROBOT_CLASS(Robot)
