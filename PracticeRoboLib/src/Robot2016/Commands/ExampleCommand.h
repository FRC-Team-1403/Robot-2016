#ifndef SRC_COMMANDS_EXAMPLE_COMMAND_H_
#define SRC_COMMANDS_EXAMPLE_COMMAND_H_

#include "../CommandBase.h"
#include "WPILib.h"

class ExampleCommand: public CommandBase
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
