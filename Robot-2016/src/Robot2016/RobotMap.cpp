#include "RobotMap.h"

std::shared_ptr<SpeedController> RobotMap::motor = 0;

void RobotMap::init(){
	cougar::CougarDebug::debugPrinter(cougar::CougarDebug::MESSAGE, "RobotMap::init running");
	// Couldn't get smart pointers working :(
	// BTW I don't actually like smart pointers
	// I'm just using them because they're less painful sometimes
	LiveWindow *lw = LiveWindow::GetInstance();

	motor.reset(new cougar::CougarSpeedController(std::shared_ptr<SpeedController>(new Victor(0)), std::string("Motor"), 1));
	//lw->AddActuator("ExampleSubsystem", "Motor", motor);
}
