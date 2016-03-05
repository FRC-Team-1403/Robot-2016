#include "Shooter/SetShooterDeckAngle.h"
#include "TravelPosition.h"
#include "Intake/LiftRollers.h"
#include "Intake/RollersIn.h"
#include "Intake/RollersInTimed.h"
#include "Intake/LiftTrigger.h"
#include "Intake/DropTrigger.h"
#include "StopAllOperator.h"


TravelPosition::TravelPosition()
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

	cougar::CougarDebug::startMethod("TravelPosition::TravelPosition");

	const float CARRYING_POS = 0;

	AddParallel(new LiftRollers());
	AddParallel(new SetShooterDeckAngle(0));
	AddSequential(new LiftTrigger());

	AddSequential(new StopAllOperator());


	cougar::CougarDebug::endMethod("TravelPosition::TravelPosition");
}
