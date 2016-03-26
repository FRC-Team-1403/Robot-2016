#ifndef DropTrigger_H
#define DropTrigger_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

#include "WPILib.h"

class DropTrigger: public cougar::CougarCommand
{
public:
	DropTrigger();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
