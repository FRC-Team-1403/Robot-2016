#ifndef StopAllDriver_H
#define StopAllDriver_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../CougarLib/CougarDebug.h"

class StopAllDriver: public Command
{
public:
	StopAllDriver();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	bool didGo;
};

#endif
