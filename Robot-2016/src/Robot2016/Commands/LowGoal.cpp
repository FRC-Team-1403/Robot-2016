#include "LowGoal.h"
#include "Shooter/SetShooterDeckAngle.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"
#include "Intake/LiftRollers.h"
#include "Intake/DropRollers.h"
#include "Intake/RollersOut.h"
#include "Shooter/PowerUpRollers.h"

LowGoal::LowGoal(std::shared_ptr<cougar::CougarJoystick> joy)
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

	AddSequential(new LiftRollers(joy));
	AddSequential(new SetShooterDeckAngle(21, joy));

	AddSequential(new DropTrigger(joy));

	AddParallel(new PowerUpRollers(-1, 1, 2, joy));
	AddSequential(new RollersOut(joy), 2);

	AddParallel(new LiftTrigger(joy));
	AddSequential(new SetShooterDeckAngle(0, joy));

}
