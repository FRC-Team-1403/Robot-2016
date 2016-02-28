#ifndef RollersOutTimed_H
#define RollersOutTimed_H

#include "Commands/Command.h"
#include "WPILib.h"

class RollersOutTimed: public Command
{
public:
	RollersOutTimed(float time);
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
