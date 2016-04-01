#ifndef DropRollers_H
#define DropRollers_H

#include "CougarLib.h"
#include "WPILib.h"

class DropRollers: public cougar::CougarCommand
{
public:
	DropRollers(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
