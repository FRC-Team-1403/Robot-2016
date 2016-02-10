#ifndef DriveTrainCommand_H
#define DriveTrainCommand_H

#include "Commands/Command.h"
#include "WPILib.h"

class DriveTrainCommand: public Command
{
public:
	DriveTrainCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
