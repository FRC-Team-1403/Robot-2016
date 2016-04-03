#include "LowBarAutonomous.h"
#include "Autonomous/LowBarAutonomous_Drive.h"
#include "LowBarPosition.h"
#include "HighGoalBatter.h"
#include "TravelPosition.h"
#include "Fire.h"

LowBarAutonomous::LowBarAutonomous(std::shared_ptr<cougar::CougarJoystick> joy)
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

	AddParallel(new DropRollers(joy));
	AddParallel(new SetShooterDeckAngle(0, joy));
	AddSequential(new LiftTrigger(joy));
	AddSequential(new Drive(1, 1, 3, joy));


	AddSequential(new LowBarAutonomous_Drive(joy));
	AddSequential(new TravelPosition(joy));
	AddSequential(new HighGoalBatter(joy));
	AddSequential(new Fire(joy));

}
