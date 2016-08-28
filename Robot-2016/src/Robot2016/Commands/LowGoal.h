#ifndef LowGoal_H
#define LowGoal_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class LowGoal: public CommandGroup
{
public:
	LowGoal(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
