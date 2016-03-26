#ifndef RollersOut_H
#define RollersOut_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"


class RollersOut : public cougar::CougarCommand
{
public:
	RollersOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
