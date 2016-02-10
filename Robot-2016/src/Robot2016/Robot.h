#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "Commands/Command.h"
#include <memory>
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "../CougarLib/CougarDebug.h"
#include "../CougarLib/TrajectoryLib/PathGenerator.h"
#include "../CougarLib/TrajectoryLib/Path.h"
#include <boost/thread.hpp>


class Robot: public IterativeRobot
{
public:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser *chooser;
	static std::shared_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<cougar::Path> path;

	virtual void RobotInit();
	virtual void DisabledInit();

	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};

#endif // ROBOT__H
