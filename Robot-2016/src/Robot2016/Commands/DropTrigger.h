#ifndef DropTrigger_H
#define DropTrigger_H

#include "Commands/Command.h"
#include "WPILib.h"

class DropTrigger: public Command
{
public:
	DropTrigger();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
