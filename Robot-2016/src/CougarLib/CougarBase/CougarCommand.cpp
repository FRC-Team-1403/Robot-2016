/*
 * CougarCommand.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarBase/CougarCommand.h>

namespace cougar {

CougarCommand::CougarCommand(std::string name, std::shared_ptr<CougarJoystick> joy, JoyInterruptFn interruptFn, double timeout)
							: Command(name, timeout) {
	this->joy_ = joy;
	this->interruptFn_ = interruptFn;
	this->doEndListener = false;
	std::thread interrupt_listener(&CougarCommand::interruptListener, this);
	interrupt_listener.detach();
}

CougarCommand::~CougarCommand() {
	this->doEndListener = true;
}

void CougarCommand::interruptListener() {
	for(;;) {
		if (this->doEndListener) {
			break;
		}

		if (this->joy_.get() != nullptr && this->interruptFn_ != nullptr) {
			if ((this->joy_.get()->*(this->interruptFn_))()) {
				if(this->GetGroup() != nullptr) {
					GetGroup()->Cancel();
				}
				else {
					Cancel();
				}
				break;
			}
		} else {
			// LOL @ real exceptions
			throw "Null pointer problems";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(10)));
	}
}

} /* namespace cougar */
