/*
 * Turn.h
 *
 *  Created on: Apr 3, 2016
 *      Author: team1403
 */

#ifndef SRC_ROBOT2016_COMMANDS_DRIVETRAIN_TURN_H_
#define SRC_ROBOT2016_COMMANDS_DRIVETRAIN_TURN_H_

#include "CougarLib.h"

class Turn : public cougar::CougarCommand {
public:
	Turn(double angle, std::shared_ptr<cougar::CougarJoystick> joy);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	virtual void stopAll() override;

	double angle;
};

#endif /* SRC_ROBOT2016_COMMANDS_DRIVETRAIN_TURN_H_ */
