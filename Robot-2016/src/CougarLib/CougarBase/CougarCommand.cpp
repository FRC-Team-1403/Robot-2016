/*
 * CougarCommand.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: Thejas
 */

#include <CougarLib/CougarBase/CougarCommand.h>

namespace cougar {

CougarCommand::CougarCommand(std::string name, std::shared_ptr<CougarJoystick> joy, bool isDefaultCommand, double timeout)
							: Command(name, timeout) {
	std::cout << "Starting CougarCommand" << this->GetName() << "\n";
	this->joy_ = joy;
	this->doEndListener = false;
	this->isDefaultCommand_ = isDefaultCommand;
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

		if (this->joy_.get() != nullptr) {
			if (this->joy_->GetButtonBothSticks() && !isDefaultCommand_ && this->IsRunning()) {
				CougarDebug::debugPrinter("Command %s interrupted", this->GetName().c_str());
				if(this->GetGroup() != nullptr) {
					GetGroup()->Cancel();
				}
				else {
					Cancel();
				}
				//break;
			}
		} else {
			// LOL @ real exceptions
			throw "Null pointer problems";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(10)));
	}
}

} /* namespace cougar */
