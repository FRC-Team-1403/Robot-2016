#include "LowBarAutonomous.h"
#include "Autonomous/LowBarAutonomous_Drive.h"
#include "Autonomous/LowBarAutonomous_ReverseDrive.h"
#include "LowBarPosition.h"
#include "HighGoalBatter.h"
#include "TravelPosition.h"
#include "Fire.h"
#include "DriveTrain/Turn.h"
#include "Shooter/SetShooterDeckAngle.h"
#include "Intake/LiftTrigger.h"
#include "Shooter/PowerUpRollers.h"
#include "Intake/DropTrigger.h"
#include "Intake/LiftRollers.h"
#include "Intake/DropRollers.h"
#include "Intake/RollersOut.h"
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

	AddSequential(new DropRollers(joy));
	AddSequential(new LowBarAutonomous_Drive(joy));

	AddSequential(new LiftRollers(joy));
	//AddSequential(new SetShooterDeckAngle(-19.5, joy));

	//AddSequential(new DropTrigger(joy));

	//AddSequential(new PowerUpRollers(0.89, 0.70, 2, joy));

	//AddParallel(new DropRollers(joy));
	//AddSequential(new LowBarAutonomous_ReverseDrive(joy));

	/*
	AddSequential(new DropRollers(joy));
	AddSequential(new SetShooterDeckAngle(0, joy));
	AddSequential(new LiftTrigger(joy));

	AddSequential(new DriveWithEncoder(10.5, joy));
	AddSequential(new Turn(-1 * M_PI / 2.25, joy));

	AddSequential(new DriveWithEncoder(-3, joy));
	AddParallel(new DropRollers(joy));

	AddSequential(new SetShooterDeckAngle(20, joy));
	AddSequential(new DropTrigger(joy));
	AddSequential(new RollersOut(joy), 2);
	AddParallel(new LiftRollers(joy));
	AddParallel(new LiftTrigger(joy));
	*/
}
