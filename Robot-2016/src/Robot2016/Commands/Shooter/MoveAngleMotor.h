#ifndef MoveAngleMotor_H
#define MoveAngleMotor_H

#include "Commands/Command.h"
#include "WPILib.h"

class MoveAngleMotor: public Command
{
public:
	MoveAngleMotor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
