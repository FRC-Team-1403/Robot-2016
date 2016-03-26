#ifndef RollersIn_H
#define RollersIn_H

#include "WPILib.h"
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"

class RollersIn: public cougar::CougarCommand
{
public:
	RollersIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
