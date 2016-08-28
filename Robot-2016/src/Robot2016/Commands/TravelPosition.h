#ifndef TravelPosition_H
#define TravelPosition_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"


class TravelPosition: public CommandGroup
{
public:
	TravelPosition(std::shared_ptr<cougar::CougarJoystick> joy);
};

#endif
