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

	double angleDelta;
	double setpointAngle;
	double initAngle;
	double error;
	double errorSum;
	double lastError;

	double power;
	double powerP;
	double powerI;
	double powerD;

	static constexpr double kP = 0.02;
	static constexpr double kI = 0;
	static constexpr double kD = 0;
};

#endif /* SRC_ROBOT2016_COMMANDS_DRIVETRAIN_TURN_H_ */
