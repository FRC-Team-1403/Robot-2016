#ifndef DropTrigger_H
#define DropTrigger_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

#include "WPILib.h"

class DropTrigger: public cougar::CougarCommand
{
public:
	DropTrigger(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
