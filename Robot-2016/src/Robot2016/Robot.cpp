#include "Robot.h"
#include "RobotMap.h"
#include "../CougarLib/CougarWPI/CougarOutput/CougarDrive.h"

std::shared_ptr<OI> Robot::oi;
std::shared_ptr<cougar::Path> Robot::path;
std::shared_ptr<DriveTrain> Robot::driveTrain;

void Robot::RobotInit()
{
	RobotMap::init();
	chooser = new SendableChooser();
	//chooser->AddDefault("Default Auto", new ExampleCommand());
	//chooser->AddObject("My Auto", new MyAutoCommand());
	SmartDashboard::PutData("Auto Modes", chooser);
	oi.reset(new OI());
	driveTrain.reset(new DriveTrain());

	std::shared_ptr<cougar::TrajectoryGenerator::Config> config(new cougar::TrajectoryGenerator::Config());
	//TODO find these values
	const double kWheelbaseWidth = 25.5/12;
	config->dt = 0.02; // Periodic methods are called every 20 ms (I think), so dt is 0.02 seconds.
	config->max_acc = 100;
	config->max_jerk = 100;
	config->max_vel = 100;

	const std::string path_name = "TEST";

	std::shared_ptr<cougar::WaypointSequence> p(new cougar::WaypointSequence(10));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(0, 0, 0)));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(7.0, 0, 0)));
	p->addWaypoint(std::shared_ptr<cougar::WaypointSequence::Waypoint>(new cougar::WaypointSequence::Waypoint(14.0, 1.0, M_PI / 12.0)));

	path = cougar::PathGenerator::makePath(p, config, kWheelbaseWidth, path_name);
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
	//SmartDashboard::PutNumber("Talon value", ((CANTalon&)exampleSubsystem->getMotor())->Get());
}

void Robot::TestPeriodic()
{
	LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot)


