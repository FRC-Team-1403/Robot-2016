#ifndef DriveWithEncoder_H
#define DriveWithEncoder_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "CougarLib/CougarBase/CougarCommand.h"

class DriveWithEncoder: public cougar::CougarCommand
{
public:
	DriveWithEncoder(float distance, std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;

	float distance;
};

#endif
