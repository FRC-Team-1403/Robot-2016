#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Subsystems/ExampleSubsystem.h"
#include <memory>
#include "OI.h"
#include "../CougarLib/CougarDebug.h"
#include "../CougarLib/TrajectoryLib/PathGenerator.h"

class Robot: public IterativeRobot
{
public:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser *chooser;
	static std::shared_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	static std::shared_ptr<ExampleSubsystem> exampleSubsystem;

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
