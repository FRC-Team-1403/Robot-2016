#ifndef CougarWait_H
#define CougarWait_H

#include "Commands/Command.h"
#include "WPILib.h"

class CougarWait: public Command
{
public:
	CougarWait(float seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	float init_time_;
	float time_;
};

#endif
