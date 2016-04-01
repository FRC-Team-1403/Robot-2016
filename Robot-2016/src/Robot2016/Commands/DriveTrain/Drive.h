#ifndef Drive_H
#define Drive_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "CougarLib/CougarBase/CougarCommand.h"

class Drive: public cougar::CougarCommand
{
public:
	Drive(float left, float right, float time, std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;

	float init_time_;
	float time_;
	float left_, right_;
};

#endif
