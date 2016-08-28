#ifndef LowBarAutonomous_ReverseDrive_H
#define LowBarAutonomous_ReverseDrive_H

#include "WPILib.h"
#include <iostream>
#include <memory>
#include <cmath>
#include "CougarLib/TrajectoryLib/TrajectoryDriveController.h"
#include "CougarLib/TrajectoryLib/TrajectoryGenerator.h"
#include "CougarLib/CougarBase/CougarCommand.h"

class LowBarAutonomous_ReverseDrive: public cougar::CougarCommand
{
public:
	LowBarAutonomous_ReverseDrive(std::shared_ptr<cougar::CougarJoystick> joy);
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
