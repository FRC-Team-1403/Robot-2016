#ifndef CalculateAngle_H
#define CalculateAngle_H

#include "Commands/Command.h"
#include "WPILib.h"

class CalculateAngle: public Command
{
public:
	CalculateAngle();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	bool isFinished;
};

#endif
