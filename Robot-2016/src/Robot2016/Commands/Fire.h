#ifndef Fire_H
#define Fire_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CougarLib.h"

class Fire: public CommandGroup
{
public:
	Fire(std::shared_ptr<cougar::CougarJoystick> joy);


};

#endif
