#ifndef LowBarPosition_H
#define LowBarPosition_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"


class LowBarPosition: public CommandGroup
{
public:
	LowBarPosition(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
