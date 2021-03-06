#ifndef LiftTrigger_H
#define LiftTrigger_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

#include "WPILib.h"

class LiftTrigger: public cougar::CougarCommand
{
public:
	LiftTrigger(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
