#ifndef SetShooterDeckAngle_H
#define SetShooterDeckAngle_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <cmath>
#include "../../../CougarLib/CougarDebug.h"

class SetShooterDeckAngle: public Command {
public:
	SetShooterDeckAngle(float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	int angle_;

	const static int ZERO_VALUE = 0;
	const static int TICKS_PER_DEGREE = 0;
};

#endif
