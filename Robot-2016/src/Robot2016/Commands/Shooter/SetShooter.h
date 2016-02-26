#ifndef SetShooter_H
#define SetShooter_H

#include "Commands/Command.h"
#include "WPILib.h"

class SetShooter: public Command {
public:
	SetShooter(float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
