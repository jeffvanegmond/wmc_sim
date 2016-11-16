#pragma once
#include <random>
#include <cmath>
#include <cfloat>

namespace wmc_sim {

enum class Result{Win, Draw, Loss};
class Elo {
public:
	Elo(double denominator, double draw_likelihood);
	Result determineResult(int r_A, int r_B, bool allow_draw = false);

private:
	void initRandom();

	std::default_random_engine rng_;
	std::uniform_real_distribution<double> uniform_{0., std::nextafter(1.0, DBL_MAX)};
	double denominator_;
	double draw_likelihood_;
};

Result invertResult(Result result);
int pointsFromResult(Result result);

}
