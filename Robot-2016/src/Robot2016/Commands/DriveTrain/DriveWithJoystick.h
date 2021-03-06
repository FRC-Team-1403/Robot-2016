#ifndef DriveWithJoystick_H
#define DriveWithJoystick_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "CougarLib/CougarBase/CougarCommand.h"

class DriveWithJoystick: public cougar::CougarCommand
{
public:
	DriveWithJoystick(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
};

#endif
