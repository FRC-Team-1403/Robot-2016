/*
 * TrajectoryGenerator.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Thejas
 */

#include "TrajectoryGenerator.h"

namespace cougar {

std::shared_ptr<TrajectoryGenerator::Strategy> TrajectoryGenerator::StepStrategy = std::shared_ptr<Strategy>(new Strategy("StepStrategy"));
std::shared_ptr<TrajectoryGenerator::Strategy> TrajectoryGenerator::TrapezoidalStrategy = std::shared_ptr<Strategy>(new Strategy("TrapezoidalStrategy"));
std::shared_ptr<TrajectoryGenerator::Strategy> TrajectoryGenerator::SCurvesStrategy = std::shared_ptr<Strategy>(new Strategy("SCurvesStrategy"));
std::shared_ptr<TrajectoryGenerator::Strategy> TrajectoryGenerator::AutomaticStrategy = std::shared_ptr<Strategy>(new Strategy("AutomaticStrategy"));

std::shared_ptr<TrajectoryGenerator::IntegrationMethod> TrajectoryGenerator::RectangularIntegration = std::shared_ptr<IntegrationMethod>(new IntegrationMethod("RectangularIntegration"));
std::shared_ptr<TrajectoryGenerator::IntegrationMethod> TrajectoryGenerator::TrapezoidalIntegration = std::shared_ptr<IntegrationMethod>(new IntegrationMethod("TrapezoidalIntegration"));


std::string TrajectoryGenerator::Strategy::toString() {
	CougarDebug::startMethod("TrajectoryGenerator::Strategy::toString");
	CougarDebug::endMethod("TrajectoryGenerator::Strategy::toString");
	return value_;
}

TrajectoryGenerator::Strategy::Strategy(std::string value) {
	CougarDebug::startMethod("TrajectoryGenerator::Strategy::Strategy");
	value_ = value;
	CougarDebug::endMethod("TrajectoryGenerator::Strategy::Strategy");
}

std::shared_ptr<Trajectory> TrajectoryGenerator::generate (
			std::shared_ptr<Config> config,
			std::shared_ptr<Strategy> strategy,
			double start_vel,
			double start_heading,
			double goal_pos,
			double goal_vel,
			double goal_heading) {
	CougarDebug::startMethod("TrajectoryGenerator::generate");
	// Choose an automatic strategy.
	if (strategy == AutomaticStrategy) {
		strategy = chooseStrategy(start_vel, goal_vel, config->max_vel);
	}

	std::shared_ptr<Trajectory> traj;
	if (strategy == StepStrategy) {
		double impulse = (goal_pos / config->max_vel) / config->dt;

		// Round down, meaning we may undershoot by less than max_vel*dt.
		// This is due to discretization and avoids a strange final
		// velocity.
		uint32_t time = (int) (floor(impulse));
		traj = secondOrderFilter(1, 1, config->dt, config->max_vel,
						config->max_vel, impulse, time, TrapezoidalIntegration);

	} else if (strategy == TrapezoidalStrategy) {
		// How fast can we go given maximum acceleration and deceleration?
		double start_discount = .5 * start_vel * start_vel / config->max_acc;
		double end_discount = .5 * goal_vel * goal_vel / config->max_acc;

		double adjusted_max_vel = fmin(config->max_vel,
						sqrt(config->max_acc * goal_pos - start_discount
										- end_discount));
		double t_rampup = (adjusted_max_vel - start_vel) / config->max_acc;
		double x_rampup = start_vel * t_rampup + .5 * config->max_acc
						* t_rampup * t_rampup;
		double t_rampdown = (adjusted_max_vel - goal_vel) / config->max_acc;
		double x_rampdown = adjusted_max_vel * t_rampdown - .5
						* config->max_acc * t_rampdown * t_rampdown;
		double x_cruise = goal_pos - x_rampdown - x_rampup;

		// The +.5 is to round to nearest
		uint32_t time = (int) ((t_rampup + t_rampdown + x_cruise
						/ adjusted_max_vel) / config->dt + .5);

		// Compute the length of the linear filters and impulse.
		uint32_t f1_length = (int) ceil((adjusted_max_vel
						/ config->max_acc) / config->dt);
		double impulse = (goal_pos / adjusted_max_vel) / config->dt
						- start_vel / config->max_acc / config->dt
						+ start_discount + end_discount;
		traj = secondOrderFilter(f1_length, 1, config->dt, start_vel,
						adjusted_max_vel, impulse, time, TrapezoidalIntegration);

	} else if (strategy == SCurvesStrategy) {
		// How fast can we go given maximum acceleration and deceleration?
		double adjusted_max_vel = fmin(config->max_vel,
						(-config->max_acc * config->max_acc + sqrt(config->max_acc
										* config->max_acc * config->max_acc * config->max_acc
										+ 4 * config->max_jerk * config->max_jerk * config->max_acc
										* goal_pos)) / (2 * config->max_jerk));

		// Compute the length of the linear filters and impulse.
		uint32_t f1_length = (int) ceil((adjusted_max_vel
						/ config->max_acc) / config->dt);
		uint32_t f2_length = (int) ceil((config->max_acc
						/ config->max_jerk) / config->dt);
		double impulse = (goal_pos / adjusted_max_vel) / config->dt;
		uint32_t time = (int) (ceil(f1_length + f2_length + impulse));
		traj = secondOrderFilter(f1_length, f2_length, config->dt, 0,
						adjusted_max_vel, impulse, time, TrapezoidalIntegration);

	} else {
		//TODO fix
		//return null;
	}

	// Now assign headings by interpolating along the path.
	// Don't do any wrapping because we don't know units.
	double total_heading_change = goal_heading - start_heading;
	for (uint32_t i = 0; i < traj->getNumSegments(); ++i) {
		traj->segments_->at(i)->heading = start_heading + total_heading_change
						* (traj->segments_->at(i)->pos)
						/ traj->segments_->at(traj->getNumSegments() - 1)->pos;
	}

	CougarDebug::endMethod("TrajectoryGenerator::generate");
	return traj;
}

std::shared_ptr<TrajectoryGenerator::Strategy> TrajectoryGenerator::chooseStrategy(double start_vel, double goal_vel,
				double max_vel) {
	CougarDebug::startMethod("TrajectoryGenerator::chooseStrategy");
	std::shared_ptr<Strategy> strategy;
	if (start_vel == goal_vel && start_vel == max_vel) {
		strategy = StepStrategy;
	} else if (start_vel == goal_vel && start_vel == 0) {
		strategy = SCurvesStrategy;
	} else {
		strategy = TrapezoidalStrategy;
	}
	CougarDebug::endMethod("TrajectoryGenerator::chooseStrategy");
	return strategy;
}

std::string TrajectoryGenerator::IntegrationMethod::toString() {
	CougarDebug::startMethod("TrajectoryGenerator::IntegrationMethod::toString");
	CougarDebug::endMethod("TrajectoryGenerator::IntegrationMethod::toString");
	return value_;
}

TrajectoryGenerator::IntegrationMethod::IntegrationMethod(std::string value) {
	CougarDebug::startMethod("TrajectoryGenerator::IntegrationMethod::IntegrationMethod");
	value_ = value;
	CougarDebug::endMethod("TrajectoryGenerator::IntegrationMethod::IntegrationMethod");
}

std::shared_ptr<Trajectory> TrajectoryGenerator::secondOrderFilter(
				uint32_t f1_length,
				uint32_t f2_length,
				double dt,
				double start_vel,
				double max_vel,
				double total_impulse,
				uint32_t length,
				std::shared_ptr<IntegrationMethod> integration) {
	CougarDebug::startMethod("TrajectoryGenerator::secondOrderFilter");
	if (length <= 0) {
		//TODO fix
		//return std::shared_pt;
	}
	std::shared_ptr<Trajectory> traj(new Trajectory(length));

	std::shared_ptr<Trajectory::Segment> last(new Trajectory::Segment());
	// First segment is easy
	last->pos = 0;
	last->vel = start_vel;
	last->acc = 0;
	last->jerk = 0;
	last->dt = dt;

	// f2 is the average of the last f2_length samples from f1, so while we
	// can recursively compute f2's sum, we need to keep a buffer for f1.
	double f1[length];
	f1[0] = (start_vel / max_vel) * f1_length;
	double f2;
	for (uint32_t i = 0; i < length; ++i) {
		// Apply input
		double input = fmin(total_impulse, 1);
		if (input < 1) {
			// The impulse is over, so decelerate
			input -= 1;
			total_impulse = 0;
		} else {
			total_impulse -= input;
		}

		// Filter through F1
		double f1_last;
		if (i > 0) {
			f1_last = f1[i - 1];
		} else {
			f1_last = f1[0];
		}
		f1[i] = fmax(0.0, fmin(f1_length, f1_last + input));

		f2 = 0;
		// Filter through F2
		for (uint32_t j = 0; j < f2_length; ++j) {
			if ((int)i - (int)j < 0) {
				break;
			}

			f2 += f1[i - j];
		}
		f2 = f2 / f1_length;

		// Velocity is the normalized sum of f2 * the max velocity
		traj->segments_->at(i)->vel = f2 / f2_length * max_vel;

		if (integration == RectangularIntegration) {
			traj->segments_->at(i)->pos = traj->segments_->at(i)->vel * dt + last->pos;
		} else if (integration == TrapezoidalIntegration) {
			traj->segments_->at(i)->pos = (last->vel
							+ traj->segments_->at(i)->vel) / 2.0 * dt + last->pos;
		}
		traj->segments_->at(i)->x = traj->segments_->at(i)->pos;
		traj->segments_->at(i)->y = 0;

		// Acceleration and jerk are the differences in velocity and
		// acceleration, respectively.
		traj->segments_->at(i)->acc = (traj->segments_->at(i)->vel - last->vel) / dt;
		traj->segments_->at(i)->jerk = (traj->segments_->at(i)->acc - last->acc) / dt;
		traj->segments_->at(i)->dt = dt;

		last = traj->segments_->at(i);
	}

	CougarDebug::endMethod("TrajectoryGenerator::secondOrderFilter");
	return traj;
}

} /* namespace cougar */
