/*
 * CougarDrive.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: Thejas
 */

// TODO Finish debugging for this class.
// Not doing it right now because TrajectoryLib needs to be fixed first.

#include "CougarDrive.h"

namespace cougar {

CougarDrive::CougarDrive(uint32_t leftPort, uint32_t rightPort,
		uint32_t leftPDPSlot, uint32_t rightPDPSlot, std::string name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<SpeedController> tmpLeft(new CougarSpeedController(leftPort, leftPDPSlot, name + "Left"));
	std::shared_ptr<SpeedController> tmpRight(new CougarSpeedController(rightPort, rightPDPSlot, name + "Right"));
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(tmpLeft, tmpRight));
	this->drive_ = tmpDrive;
	this->name_ = name;
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::CougarDrive(uint32_t leftPort1, uint32_t leftPort2,
		uint32_t rightPort1, uint32_t rightPort2,
		uint32_t leftPDPSlot1, uint32_t leftPDPSlot2,
		uint32_t rightPDPSlot1, uint32_t rightPDPSlot2,
		std::string name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<SpeedController> tmpLeft(new CougarSpeedControllerAggregate(leftPort1, leftPort2,
			leftPDPSlot1, leftPDPSlot2, name + "Left"));
	std::shared_ptr<SpeedController> tmpRight(new CougarSpeedControllerAggregate(rightPort1, rightPort2,
				rightPDPSlot1, rightPDPSlot2, name + "Right"));
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(tmpLeft, tmpRight));
	this->drive_ = tmpDrive;
	this->name_ = name;
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}


CougarDrive::CougarDrive(std::shared_ptr<SpeedController> left, std::shared_ptr<SpeedController> right, std::string name) {
	CougarDebug::startMethod("CougarDrive::CougarDrive " + name);
	std::shared_ptr<RobotDrive> tmpDrive(new RobotDrive(left, right));
	this->drive_ = tmpDrive;
	this->name_ = name;
	CougarDebug::endMethod("CougarDrive::CougarDrive " + this->GetName());
}

CougarDrive::~CougarDrive() {
	CougarDebug::startMethod("CougarDrive::~CougarDrive " + this->GetName());
	CougarDebug::endMethod("CougarDrive::~CougarDrive " + this->GetName());
}

void CougarDrive::Drive(float outputMagnitude, float curve) const{
	this->drive_->Drive(outputMagnitude, curve);
}

void CougarDrive::TankDrive(float leftPower, float rightPower, bool squaredInputs /* = false */) {
	this->drive_->TankDrive(leftPower, rightPower, squaredInputs);
}


void CougarDrive::TankDrive(std::shared_ptr<CougarJoystick> joystick, bool reversed,  bool squaredInputs /* = true */) {
	int reverse = reversed ? -1 : 1;
	this->drive_->TankDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickRightAxisY() * this->speedFactor(joystick) * reverse, squaredInputs);
}
void CougarDrive::ArcadeDrive(std::shared_ptr<CougarJoystick> joystick, int stick /* LEFT or RIGHT */ , bool reversed, bool squaredInputs /* = true */) {
	int reverse = reversed ? -1 : 1;
	if (stick == LEFT) {
		this->drive_->ArcadeDrive(joystick->GetStickLeftAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickLeftAxisX() * this->speedFactor(joystick) * reverse, squaredInputs);
	} else if (stick == RIGHT) {
		this->drive_->ArcadeDrive(joystick->GetStickRightAxisY() * this->speedFactor(joystick) * reverse, joystick->GetStickRightAxisX() * this->speedFactor(joystick) * reverse, squaredInputs);
	} else {
		CougarDebug::debugPrinter(CougarDebug::DEBUG_LEVEL::ISSUE, "An invalid analog stick has been specified...\n\n");
	}
}

void CougarDrive::SetSensitivity(float sensitivity) {
	CougarDebug::startMethod("CougarDrive::SetSensitivity");
	this->drive_->SetSensitivity(sensitivity);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "sensitivity set to " + std::to_string(sensitivity));
	CougarDebug::endMethod("CougarDrive::SetSensitivity");
}

void CougarDrive::SetMaxOutput(double maxOutput) {
	CougarDebug::startMethod("CougarDrive::SetMaxOutput");
	this->drive_->SetMaxOutput(maxOutput);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "max output set to " + std::to_string(maxOutput));
	CougarDebug::endMethod("CougarDrive::SetMaxOutput");
}

void CougarDrive::SetExpiration(float timeout) {
	CougarDebug::startMethod("CougarDrive::SetExpiration");
	this->drive_->SetExpiration(timeout);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "expiration set to " + std::to_string(timeout));
	CougarDebug::endMethod("CougarDrive::SetExpiration");
}

float CougarDrive::GetExpiration() const {
	return this->drive_->GetExpiration();
}

bool CougarDrive::IsAlive() const {
	return this->drive_->IsAlive();
}

void CougarDrive::StopMotor() {
	this->drive_->StopMotor();
}

bool CougarDrive::IsSafetyEnabled() const {
	return this->drive_->IsSafetyEnabled();
}

void CougarDrive::SetSafetyEnabled(bool enabled) {
	CougarDebug::startMethod("CougarDrive::SetSafetyEnabled");
	this->drive_->SetSafetyEnabled(enabled);
	CougarDebug::debugPrinter(CougarDebug::MESSAGE, "CougarDrive " + this->GetName() + "safety set to " + std::to_string(enabled));
	CougarDebug::endMethod("CougarDrive::SetSafetyEnabled");
}
std::string CougarDrive::GetName() const {
	return this->name_;
}

const char *CougarDrive::GetCName() const {
	return this->name_.c_str();
}

std::shared_ptr<RobotDrive> CougarDrive::GetDrive() {
	return this->drive_;
}

float CougarDrive::speedFactor(std::shared_ptr<CougarJoystick> joystick) {
	const float SPEED_FACTOR = 0.5;
	return joystick->GetButtonY() ? SPEED_FACTOR : 1;
}

} /* namespace cougar */
