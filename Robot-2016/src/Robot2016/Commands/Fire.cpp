#include "Fire.h"
#include "Shooter/SetShooterDeckAngle.h"
#include "Shooter/PowerUpRollers.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"
#include "StopAllOperator.h"
#include "CougarWait.h"

Fire::Fire()
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


	AddSequential(new DropTrigger());

	AddSequential(new PowerUpRollers(100, 100));

	AddSequential(new LiftTrigger());

	AddSequential(new CougarWait(0.5));

	AddSequential(new StopAllOperator());
}
