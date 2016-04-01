#ifndef IntakeBall_H
#define IntakeBall_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"


class IntakeBall: public CommandGroup
{
public:
	IntakeBall(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
