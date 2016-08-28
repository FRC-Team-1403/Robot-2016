#ifndef DriveForwardAutonomous_H
#define DriveForwardAutonomous_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class DriveForwardAutonomous: public CommandGroup
{
public:
	DriveForwardAutonomous(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
