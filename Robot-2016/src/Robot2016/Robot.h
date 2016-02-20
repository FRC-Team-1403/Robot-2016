#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <Robot2016/Commands/LowBarAutonomous_Drive.h>
#include "WPILib.h"
#include <memory>
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Intake.h"
#include "../CougarLib/CougarDebug.h"
#include "../CougarLib/TrajectoryLib/PathGenerator.h"
#include "../CougarLib/TrajectoryLib/Path.h"
//#include <boost/thread.hpp>


class Robot: public IterativeRobot
{
public:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser *chooser;
	static std::shared_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();

	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<Shooter> shooter;
	static std::shared_ptr<Intake> intake;

	static std::shared_ptr<cougar::Path> lowBarPath;
	static int buffer;
	static bool enabled;
	static bool autonomous;
	static bool teleop;
	static bool test;

	static bool isEnabled();
	static bool isAutonomous();
	static bool isTeleop();
	static bool isTest();

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
private:
	static void initModes();
	static void setMode(bool e, bool a, bool t1, bool t2);
	virtual void update();
};

#endif // ROBOT__H
