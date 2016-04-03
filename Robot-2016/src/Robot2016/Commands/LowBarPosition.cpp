#include "Shooter/SetShooterDeckAngle.h"
#include "LowBarPosition.h"
#include "Intake/DropRollers.h"
#include "Intake/RollersIn.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"


LowBarPosition::LowBarPosition(std::shared_ptr<cougar::CougarJoystick> joy)
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	cougar::CougarDebug::startMethod("LowBarPosition::LowBarPosition");

	const float CARRYING_POS = 0;

	AddParallel(new DropRollers(joy));
	AddParallel(new SetShooterDeckAngle(0, joy));
	AddSequential(new LiftTrigger(joy));

	cougar::CougarDebug::endMethod("LowBarPosition::LowBarPosition");
}
