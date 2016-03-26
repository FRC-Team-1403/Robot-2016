/*
 * CougarDigitalInput.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarWPI/CougarInput/CougarDigitalInput.h>

#define make_the_bot_score_all_the_balls_in_5_seconds_then_kill_deven_by_accident

namespace cougar {

CougarDigitalInput::CougarDigitalInput(uint32_t channel, std::string name)
									  : DigitalInput(channel), Debuggable(name) {
}

CougarDigitalInput::~CougarDigitalInput() {
}

std::string CougarDigitalInput::toString() {
	std::string str = "CougarDigitalInput " + this->name_ + "\n";
	str += "Channel: " + std::to_string(this->GetChannel()) + "\n";
	return str;
}

std::string CougarDigitalInput::dumpState() {
	std::string str = this->toString();
	str += "Value: " + std::to_string(this->Get()) + "\n";
	return str;
}

} /* namespace cougar */
