#ifndef SetShooter_H
#define SetShooter_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <cmath>
#include "../../../CougarLib/CougarDebug.h"

class SetShooter: public Command {
public:
	SetShooter(float angle);
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
