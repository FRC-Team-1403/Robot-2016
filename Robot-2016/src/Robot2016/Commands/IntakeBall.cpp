#include "Shooter/SetShooterDeckAngle.h"
#include "IntakeBall.h"
#include "Intake/DropRollers.h"
#include "Intake/RollersIn.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"


IntakeBall::IntakeBall(std::shared_ptr<cougar::CougarJoystick> joy)
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

	cougar::CougarDebug::startMethod("IntakeBall::IntakeBall");

	const float INTAKE_POS = -15;
	const float CARRYING_POS = 0;

	AddSequential(new LiftTrigger(joy));

	AddParallel(new DropRollers(joy));
	AddParallel(new SetShooterDeckAngle(INTAKE_POS, joy));
	AddSequential(new DropTrigger(joy));

	AddSequential(new RollersIn(joy));

	AddParallel(new LiftTrigger(joy));
	AddSequential(new SetShooterDeckAngle(CARRYING_POS, joy));


	cougar::CougarDebug::endMethod("IntakeBall::IntakeBall");
}
