#ifndef LowBarAutonomous_H
#define LowBarAutonomous_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class LowBarAutonomous: public CommandGroup
{
public:
	LowBarAutonomous(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
