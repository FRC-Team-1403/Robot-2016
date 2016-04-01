#ifndef LowBarAutonomous_Drive_H
#define LowBarAutonomous_Drive_H

#include "WPILib.h"
#include <iostream>
#include <memory>
#include <cmath>
#include "CougarLib/TrajectoryLib/TrajectoryDriveController.h"
#include "CougarLib/TrajectoryLib/TrajectoryGenerator.h"
#include "CougarLib/CougarBase/CougarCommand.h"

class LowBarAutonomous_Drive: public cougar::CougarCommand
{
public:
	LowBarAutonomous_Drive(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

protected:
	virtual void stopAll() override;

private:
	std::shared_ptr<cougar::TrajectoryDriveController> driveController;
	double start_time;
};

#endif
