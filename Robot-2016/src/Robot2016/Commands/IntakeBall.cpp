#include "IntakeBall.h"
#include "Intake/DropRollers.h"
#include "Intake/RollersIn.h"
#include "Intake/RollersInTimed.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"
#include "Shooter/SetShooter.h"
#include "StopAllOperator.h"


IntakeBall::IntakeBall()
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

	const float INTAKE_POS = 0;
	const float CARRYING_POS = 0;

	AddSequential(new LiftTrigger());

	AddParallel(new DropRollers());
	AddParallel(new SetShooter(INTAKE_POS));
	AddSequential(new DropTrigger());

	AddSequential(new RollersIn());

	AddParallel(new LiftTrigger());
	AddSequential(new SetShooter(CARRYING_POS));

	AddSequential(new StopAllOperator());

	cougar::CougarDebug::endMethod("IntakeBall::IntakeBall");
}
