#ifndef MoveShooter_H
#define MoveShooter_H

#include "WPILib.h"
#include "Commands/Command.h"

class MoveShooter: public Command
{
public:
	MoveShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
