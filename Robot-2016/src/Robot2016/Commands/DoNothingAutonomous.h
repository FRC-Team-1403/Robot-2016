#ifndef DoNothingAutonomous_H
#define DoNothingAutonomous_H

#include "Commands/Command.h"
#include "WPILib.h"

class DoNothingAutonomous: public Command
{
public:
	DoNothingAutonomous();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
