#ifndef RollersInTimed_H
#define RollersInTimed_H

#include "Commands/Command.h"
#include "WPILib.h"

class RollersInTimed: public Command
{
public:
	RollersInTimed(float time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

protected:
	float start_time_;
	float time_;
};

#endif
