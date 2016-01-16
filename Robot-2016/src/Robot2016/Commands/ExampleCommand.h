#ifndef ExampleCommand_H
#define ExampleCommand_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../Subsystems/ExampleSubsystem.h"
#include "../../CougarLib/CougarDebug.h"

class ExampleCommand: public Command
{
public:
	ExampleCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
