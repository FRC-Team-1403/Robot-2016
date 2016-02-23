#ifndef ControlIntake_H
#define ControlIntake_H

#include "WPILib.h"
#include "Commands/Command.h"

class ControlIntake: public Command
{
public:
	ControlIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
