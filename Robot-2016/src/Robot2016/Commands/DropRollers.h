#ifndef DropRollers_H
#define DropRollers_H

#include "Commands/Command.h"
#include "WPILib.h"

class DropRollers: public Command
{
public:
	DropRollers();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
