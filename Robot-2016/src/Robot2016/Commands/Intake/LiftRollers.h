#ifndef LiftRollers_H
#define LiftRollers_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarWPI/CougarOutput/CougarDoubleSolenoid.h"
#include "WPILib.h"

class LiftRollers: public Command
{
public:
	LiftRollers();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
