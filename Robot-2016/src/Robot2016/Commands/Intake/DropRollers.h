#ifndef DropRollers_H
#define DropRollers_H

#include "Commands/Command.h"
#include "../../../CougarLib/CougarWPI/CougarOutput/CougarDoubleSolenoid.h"
#include "CougarLib/CougarBase/CougarCommand.h"

#include "WPILib.h"

class DropRollers: public cougar::CougarCommand
{
public:
	DropRollers();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
