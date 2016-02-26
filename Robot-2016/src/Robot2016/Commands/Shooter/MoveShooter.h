#ifndef MoveShooter_H
#define MoveShooter_H

#include "Commands/Command.h"
#include "WPILib.h"

class MoveShooter: public Command
{
public:
	MoveShooter(float deltaAngle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
