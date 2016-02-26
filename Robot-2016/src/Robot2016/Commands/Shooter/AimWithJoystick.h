#ifndef DriveWithJoystick_H
#define DriveWithJoystick_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../../CougarLib/CougarDebug.h"


class AimWithJoystick: public Command
{
public:
	AimWithJoystick();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
