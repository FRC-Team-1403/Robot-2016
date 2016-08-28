#ifndef RollersIn_H
#define RollersIn_H

#include "WPILib.h"
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

class RollersIn: public cougar::CougarCommand
{
public:
	RollersIn(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
