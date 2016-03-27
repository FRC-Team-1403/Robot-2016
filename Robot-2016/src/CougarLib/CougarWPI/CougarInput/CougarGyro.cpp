/*
 * CougarGyro.cpp
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#include <CougarLib/CougarWPI/CougarInput/CougarGyro.h>

namespace cougar {

/**
 * Gyro constructor using the Analog Input channel number.
 *
 * @param channel The analog channel the gyro is connected to. Gyros
											can only be used on on-board Analog Inputs 0-1.
 */
CougarGyro::CougarGyro(int32_t channel, std::string name) :
		CougarGyro(std::shared_ptr<AnalogInput>(new AnalogInput(channel)), name) {
	CougarDebug::startMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel) + std::string("]")).c_str());
	CougarDebug::endMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel) + std::string("]")).c_str());

}

/**
 * Gyro constructor with a precreated AnalogInput object.
 * Use this constructor when the analog channel needs to be shared.
 * This object will not clean up the AnalogInput object when using this
 * constructor.
 * Gyros can only be used on on-board channels 0-1.
 * @param channel A pointer to the AnalogInput object that the gyro is connected
 * to.
 */
CougarGyro::CougarGyro(AnalogInput *channel, std::string name)
		: CougarGyro(
					std::shared_ptr<AnalogInput>(channel, NullDeleter<AnalogInput>()), name) {
	CougarDebug::startMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
	CougarDebug::endMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
}

/**
 * Gyro constructor with a precreated AnalogInput object.
 * Use this constructor when the analog channel needs to be shared.
 * This object will not clean up the AnalogInput object when using this
 * constructor
 * @param channel A pointer to the AnalogInput object that the gyro is
 * connected to.
 */
CougarGyro::CougarGyro(std::shared_ptr<AnalogInput> channel, std::string name)
		:AnalogGyro(channel), Debuggable(name) {
	CougarDebug::startMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
	this->m_channel = channel->GetChannel();
	CougarDebug::endMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
}

/**
 * Gyro constructor using the Analog Input channel number with parameters for
 * presetting the center and offset values. Bypasses calibration.
 *
 * @param channel The analog channel the gyro is connected to. Gyros
 *				can only be used on on-board Analog Inputs 0-1.
 * @param center Preset uncalibrated value to use as the accumulator center value.
 * @param offset Preset uncalibrated value to use as the gyro offset.
 */
CougarGyro::CougarGyro(int32_t channel, uint32_t center, float offset, std::string name)
	: AnalogGyro(channel, center, offset), Debuggable(name) {
	CougarDebug::startMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel) + std::string("]")).c_str());
	this->m_channel = channel;
	CougarDebug::endMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel) + std::string("]")).c_str());
}

/**
 * Gyro constructor with a precreated AnalogInput object and calibrated parameters.
 * Use this constructor when the analog channel needs to be shared.
 * This object will not clean up the AnalogInput object when using this
 * constructor
 * @param channel A pointer to the AnalogInput object that the gyro is
 * connected to.
 */
CougarGyro::CougarGyro(std::shared_ptr<AnalogInput> channel, uint32_t center, float offset, std::string name)
	: AnalogGyro(channel, center, offset), Debuggable(name) {
	CougarDebug::startMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
	this->m_channel = channel->GetChannel();
	CougarDebug::endMethod((std::string("CougarGyro::CougarGyro [channel ") + std::to_string(channel->GetChannel()) + std::string("]")).c_str());
}

std::string CougarGyro::toString() {
	std::string str = "CougarGyro " + this->name_ + "\n";
	str += "Channel: " + std::to_string(this->m_channel) + "\n";
	return str;
}

std::string CougarGyro::dumpState() {
	std::string str = this->toString();
	str += "Angle: " + std::to_string(this->GetAngle()) + "\n";
	str += "Rate: " + std::to_string(this->GetRate()) + "\n";
	str += "Center: " + std::to_string(this->GetCenter()) + "\n";
	str += "Offset: " + std::to_string(this->GetOffset()) + "\n";
	return str;
}

} /* namespace cougar */
