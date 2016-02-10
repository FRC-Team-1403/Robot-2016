#ifndef AutonomousDrive_H
#define AutonomousDrive_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <iostream>
#include <memory>
#include "../../CougarLib/TrajectoryLib/TrajectoryDriveController.h"

class AutonomousDrive: public Command
{
public:
	AutonomousDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<cougar::TrajectoryDriveController> driveController;
	double start_time;
};

#endif
