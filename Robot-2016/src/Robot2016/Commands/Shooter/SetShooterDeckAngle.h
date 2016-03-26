#ifndef SetShooterDeckAngle_H
#define SetShooterDeckAngle_H

#include "Commands/Command.h"
#include "WPILib.h"
#include <cmath>
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarConstants.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"


class SetShooterDeckAngle: public cougar::CougarCommand {
public:
	SetShooterDeckAngle(float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;

	int angle_;
};

#endif
