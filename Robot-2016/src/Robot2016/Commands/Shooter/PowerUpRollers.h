#ifndef PowerUpRollers_H
#define PowerUpRollers_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../../CougarLib/CougarConstants.h"
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

#include <cmath>

class PowerUpRollers: public cougar::CougarCommand
{
public:
	PowerUpRollers(float topRollerPower, float bottomRollerPower, float time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;

	float topRollerPower_, bottomRollerPower_;
	float init_time_;
	float time_;
};

#endif
