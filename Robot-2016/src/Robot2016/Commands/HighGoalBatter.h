#ifndef HighGoalBatter_H
#define HighGoalBatter_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class HighGoalBatter: public CommandGroup
{
public:
	HighGoalBatter(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
