#include "Robot.h"
#include "RobotMap.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

std::shared_ptr<OI> Robot::oi;
std::shared_ptr<cougar::Path> Robot::path;
std::shared_ptr<DriveTrain> Robot::driveTrain;

void Robot::RobotInit()
{

	cougar::CougarDebug::debugPrinter("Robot::RobotInit started");
	cougar::CougarDebug::init();
	cougar::CougarDebug::debugPrinter("Initialization part 1 started");
	RobotMap::init();
	cougar::CougarDebug::debugPrinter("Initialization part 1 finished");

	cougar::CougarDebug::debugPrinter("SendableChooser initialization started");
	chooser = new SendableChooser();
	chooser->AddDefault("Default Auto", new AutonomousDrive());
	SmartDashboard::PutData("Auto Modes", chooser);
	cougar::CougarDebug::debugPrinter("SendableChooser initialization finished");

	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization started");
	oi.reset(new OI());
	driveTrain.reset(new DriveTrain());
	cougar::CougarDebug::debugPrinter("OI/Subsystem initialization finished");

	cougar::CougarDebug::debugPrinter("Motion mapping initialization started");
	std::shared_ptr<cougar::TrajectoryGenerator::Config> config(new cougar::TrajectoryGenerator::Config());
	cougar::CougarDebug::debugPrinter("Motion mapping initialization checkpoint 1");
	//TODO find these values
	const double kWheelbaseWidth = 22.25/12;
	config->dt = 0.02; // Periodic methods are called every 20 ms (I think), so dt is 0.02 seconds.
	config->max_acc = 40.0;
	config->max_jerk = 60.0;
	config->max_vel = 7.8;
	cougar::CougarDebug::debugPrinter("Motion mapping initialization checkpoint 2");
	const std::string path_name = "TEST";

	std::shared_ptr<cougar::WaypointSequence> p(new cougar::WaypointSequence(10));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(0, 0, 0)));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(2, 0, M_PI/12)));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(4, 0, M_PI/6)));
	cougar::CougarDebug::debugPrinter("Motion mapping initialization checkpoint 3");
	path = cougar::PathGenerator::makePath(p, config, kWheelbaseWidth, path_name);
	cougar::CougarDebug::debugPrinter("Motion mapping initialization finished");
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic()
{
	Scheduler::GetInstance()->Run();
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
	/* std::string autoSelected = SmartDashboard::GetString("Auto Selector", "Default");
	if(autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	} else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	autonomousCommand.reset((Command *)chooser->GetSelected());

	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic()
{
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic()
{
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("Joystick value", oi->GetJoystick()->GetStickLeftAxisY());
	SmartDashboard::PutNumber("Position", driveTrain->getDistance());
	SmartDashboard::PutNumber("Velocity", driveTrain->getVelocity());
	SmartDashboard::PutNumber("Acceleration", driveTrain->getAcceleration());
	SmartDashboard::PutNumber("Jerk", driveTrain->getJerk());
	SmartDashboard::PutNumber("Angle", driveTrain->getGyroAngleInRadians());
	SmartDashboard::PutNumber("Angular Velocity", driveTrain->getAngularVelocity());


	//SmartDashboard::PutNumber("Talon value", ((CANTalon&)exampleSubsystem->getMotor())->Get());
}

void Robot::TestPeriodic()
{
	LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot)
