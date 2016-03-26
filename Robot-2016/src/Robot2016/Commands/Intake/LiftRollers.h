#ifndef LiftRollers_H
#define LiftRollers_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarWPI/CougarOutput/CougarDoubleSolenoid.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

#include "WPILib.h"

class LiftRollers: public cougar::CougarCommand
{
public:
	LiftRollers();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
