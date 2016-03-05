#include "LowGoal.h"
#include "Intake/RollersOutTimed.h"
#include "CougarWait.h"
#include "Shooter/SetShooterDeckAngle.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"
#include "Intake/LiftRollers.h"
#include "Intake/DropRollers.h"
#include "StopAllOperator.h"

LowGoal::LowGoal()
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

	AddParallel(new DropRollers());
	AddSequential(new SetShooterDeckAngle(10));

	AddSequential(new DropTrigger());

	AddSequential(new RollersOutTimed(2));

	AddParallel(new LiftRollers());
	AddParallel(new LiftTrigger());

	AddSequential(new StopAllOperator());
}
