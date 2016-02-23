#ifndef LiftTrigger_H
#define LiftTrigger_H

#include "Commands/Command.h"
#include "WPILib.h"

class LiftTrigger: public Command
{
public:
	LiftTrigger();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
