#ifndef LowBarAutonomous_Drive_H
#define LowBarAutonomous_Drive_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <iostream>
#include <memory>
#include <cmath>
#include "../../CougarLib/TrajectoryLib/TrajectoryDriveController.h"
#include "../../CougarLib/TrajectoryLib/TrajectoryGenerator.h"

class LowBarAutonomous_Drive: public Command
{
public:
	LowBarAutonomous_Drive();
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
