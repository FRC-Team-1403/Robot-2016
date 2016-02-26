#ifndef StopAllOperator_H
#define StopAllOperator_H

#include "Commands/Command.h"
#include "WPILib.h"

class StopAllOperator: public Command
{
public:
	StopAllOperator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
