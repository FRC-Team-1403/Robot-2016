#ifndef Drive_H
#define Drive_H

#include "WPILib.h"
#include "Commands/Command.h"

class Drive: public Command
{
public:
	Drive(float left, float right, float time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	float init_time_;
	float time_;
	float left_, right_;
};

#endif
