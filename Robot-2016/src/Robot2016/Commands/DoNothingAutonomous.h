#ifndef DoNothingAutonomous_H
#define DoNothingAutonomous_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../CougarLib/CougarBase/CougarCommand.h"


class DoNothingAutonomous: public cougar::CougarCommand
{
public:
	DoNothingAutonomous(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	virtual void stopAll() override {}
};

#endif
