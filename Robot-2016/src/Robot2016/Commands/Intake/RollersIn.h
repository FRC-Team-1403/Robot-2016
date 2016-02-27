#ifndef RollersIn_H
#define RollersIn_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../../CougarLib/CougarDebug.h"

class RollersIn: public Command
{
public:
	RollersIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
