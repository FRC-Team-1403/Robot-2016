/*
 * TrajectoryGenerator.h
 *
 *	Created on: Feb 6, 2016
 *			Author: Thejas
 */

#ifndef SRC_TRAJECTORYGENERATOR_H_
#define SRC_TRAJECTORYGENERATOR_H_

#include "Trajectory.h"
#include <string>
#include <memory>
#include <cmath>

namespace cougar {

class TrajectoryGenerator {
public:

	///// INNER CLASSES /////
	class Config {
	public:
		double dt;
		double max_vel;
		double max_acc;
		double max_jerk;
	};

	class Strategy {
	public:
		virtual std::string toString();

		Strategy(std::string value);
	private:
		std::string value_;
	};



	///// CONSTANTS /////
	// Move from the start to the goal at a constant velocity.	Acceleration and
	// jerk limits are ignored, and start and goal vel are ignored (since the
	// velocity at all times will be max_vel).
	static std::shared_ptr<Strategy> StepStrategy;;

	// Move from the start to the goal with a trapezoidal speed profile.
	// Jerk limits are ignored.
	static std::shared_ptr<Strategy> TrapezoidalStrategy;

	// Move from the start tot he goal with a S-curve speed profile.	All limits
	// are obeyed, but only point-to-point moves (start_vel = goal_vel = 0) are
	// currently supported.
	static std::shared_ptr<Strategy> SCurvesStrategy;

	// Choose one of the above strategies based on the inputs.
	static std::shared_ptr<Strategy> AutomaticStrategy;


	/**
	 * Generate a trajectory from a start state to a goal state.
	 *
	 * Read the notes on each of the Strategies defined above, as certain
	 * arguments are ignored for some strategies.
	 *
	 * @param config Definition of constraints and sampling rate (WARNING: Some
	 * may be ignored)
	 * @param strategy Which generator to use
	 * @param start_vel The starting velocity (WARNING: May be ignored)
	 * @param start_heading The starting heading
	 * @param goal_pos The goal position
	 * @param goal_vel The goal velocity (WARNING: May be ignored)
	 * @param goal_heading The goal heading
	 * @return A Trajectory that satisfies the relevant constraints and end
	 * conditions.
	 */
	static std::shared_ptr<Trajectory> generate (
				std::shared_ptr<Config> config,
				std::shared_ptr<Strategy> strategy,
				double start_vel,
				double start_heading,
				double goal_pos,
				double goal_vel,
				double goal_heading);

	static std::shared_ptr<Strategy> chooseStrategy(double start_vel, double goal_vel,
					double max_vel);

private:
	class IntegrationMethod {
	public:
		std::string toString();

		IntegrationMethod(std::string value);

	private:
		std::string value_;
	};

	static std::shared_ptr<IntegrationMethod> RectangularIntegration;
	static std::shared_ptr<IntegrationMethod> TrapezoidalIntegration;


	static std::shared_ptr<Trajectory> secondOrderFilter(
					uint32_t f1_length,
					uint32_t f2_length,
					double dt,
					double start_vel,
					double max_vel,
					double total_impulse,
					uint32_t length,
					std::shared_ptr<IntegrationMethod> integration);


};

} /* namespace cougar */

#endif /* SRC_TRAJECTORYGENERATOR_H_ */
