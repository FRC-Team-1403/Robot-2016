#ifndef PowerUpRollers_H
#define PowerUpRollers_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../../CougarLib/CougarConstants.h"
#include "../../../CougarLib/CougarDebug.h"
#include <cmath>

class PowerUpRollers: public Command
{
public:
	PowerUpRollers(float topRollerPower, float bottomRollerPower);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	float topRollerPower_, bottomRollerPower_;
};

#endif