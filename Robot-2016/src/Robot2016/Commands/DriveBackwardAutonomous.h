#ifndef DriveBackwardAutonomous_H
#define DriveBackwardAutonomous_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class DriveBackwardAutonomous: public CommandGroup
{
public:
	DriveBackwardAutonomous(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
