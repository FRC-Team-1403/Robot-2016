#ifndef SetShooterDeckAngle_H
#define SetShooterDeckAngle_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <cmath>
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarConstants.h"

class SetShooterDeckAngle: public Command {
public:
	SetShooterDeckAngle(float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	int angle_;
};

#endif
