#ifndef DriveWithJoystick_H
#define DriveWithJoystick_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../../CougarLib/CougarDebug.h"
#include "../../../CougarLib/CougarBase/CougarCommand.h"



class AimWithJoystick: public cougar::CougarCommand
{
public:
	AimWithJoystick(std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;
	float cam;
};

#endif
