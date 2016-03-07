/*
 * CougarConstants.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARCONSTANTS_H_
#define SRC_COUGARLIB_COUGARCONSTANTS_H_

#include <cmath>

namespace cougar {

class CougarConstants {
public:

/**********************************Ports**********************************/

	// Drive Train
	static const uint8_t DRIVETRAIN_VICTOR_PORT_LEFT_1 = 2;
	static const uint8_t DRIVETRAIN_VICTOR_PORT_LEFT_2 = 3;
	static const uint8_t DRIVETRAIN_VICTOR_PORT_RIGHT_1 = 0;
	static const uint8_t DRIVETRAIN_VICTOR_PORT_RIGHT_2 = 1;

	static const uint8_t DRIVETRAIN_VICTOR_PDP_SLOT_LEFT_1 = 2;
	static const uint8_t DRIVETRAIN_VICTOR_PDP_SLOT_LEFT_2 = 3;
	static const uint8_t DRIVETRAIN_VICTOR_PDP_SLOT_RIGHT_1 = 0;
	static const uint8_t DRIVETRAIN_VICTOR_PDP_SLOT_RIGHT_2 = 1;

	static const uint8_t DRIVETRAIN_ENCODER_LEFT_ACHANNEL = 0;
	static const uint8_t DRIVETRAIN_ENCODER_LEFT_BCHANNEL = 1;
	static const uint8_t DRIVETRAIN_ENCODER_RIGHT_ACHANNEL = 3;
	static const uint8_t DRIVETRAIN_ENCODER_RIGHT_BCHANNEL = 2;

	static const uint8_t DRIVETRAIN_GYRO_CHANNEL = 0;

	// Shooter
	static const uint8_t SHOOTER_ROLLER_TOP_CANTALON_PORT = 5;
	static const uint8_t SHOOTER_ROLLER_BOTTOM_CANTALON_PORT = 4;
	static const uint8_t SHOOTER_DECK_ANGLE_CANTALON_PORT = 3;
	static const uint8_t SHOOTER_CAMERA_SERVO_PORT = 5;

	// Intake
	static const uint8_t INTAKE_ROLLER_VICTOR_PORT = 4;
	static const uint8_t INTAKE_ROLLER_VICTOR_PDP_SLOT = 4;

	static const uint8_t INTAKE_ANGLE_DOUBLESOLENOID_FORWARD_CHANNEL = 5;
	static const uint8_t INTAKE_ANGLE_DOUBLESOLENOID_REVERSE_CHANNEL = 1;

	static const uint8_t INTAKE_TRIGGER_SOLENOID_CHANNEL = 4;

	static const uint8_t INTAKE_BALL_LIMIT_SWITCH_DIGITAL_INPUT_PORT = 4;


/**********************************Values**********************************/

	// Drive Train
	static constexpr float DRIVE_ENCODER_TICKS_PER_FOOT = ((8 * M_PI) / 12) / 256;

	// Shooter
	static const bool SHOOTER_ROLLER_TOP_CANTALON_REVERSE_SENSOR = true;
	static const bool SHOOTER_ROLLER_BOTTOM_CANTALON_REVERSE_SENSOR = true;
	static const bool SHOOTER_DECK_ANGLE_CANTALON_REVERSE_SENSOR = false;

	static const int SHOOTER_DECK_ANGLE_POTENTIOMETER_TURNS = 1;
	static const int SHOOTER_DECK_ANGLE_FORWARD_LIMIT = 604;
	static const int SHOOTER_DECK_ANGLE_REVERSE_LIMIT = 351;

	static const int SHOOTER_DECK_ANGLE_ZERO = 549;
	static const int SHOOTER_DECK_TICKS_PER_DEGREE = 5;

	static const int SHOOTER_ROLLER_MAX_SPEED = 4500;

	static constexpr float SHOOTER_ROLLER_ENCODER_TICKS_PER_REV = 512.0 / 5.0;

	//Projectile Motion x, vi, y, a
	static constexpr float ACCEPTABLE_ERROR_IN_ANGLE = .1;
	static constexpr float HEIGHT_OF_SHOOTER = 2.0/3.0; //h 8 inches
	static constexpr float VERTICAL_DISTANCE_FROM_TOWER = 97.0/12.0 - HEIGHT_OF_SHOOTER; //y
	static constexpr float DISTANCE_FROM_CAMERA = 14.0/12.0; //14 inches
	static constexpr float SPIN_CONSTANT = 0; //s, test for this
	static constexpr float VERTICAL_ACCELERATION = 32.174 + SPIN_CONSTANT; //a
	static constexpr float INITIAL_VELOCITY = 41.86; //vi

private:
	CougarConstants();
	virtual ~CougarConstants() = default;
};

}

#endif /* SRC_COUGARLIB_COUGARCONSTANTS_H_ */
