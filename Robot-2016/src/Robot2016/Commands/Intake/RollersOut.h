#ifndef RollersOut_H
#define RollersOut_H

#include "Commands/Command.h"
#include "WPILib.h"

class RollersOut: public Command
{
public:
	RollersOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
