#include <elo.h>

#include <iostream>

namespace wmc_sim {

Elo::Elo(double denominator, double draw_likelihood) : denominator_(denominator), draw_likelihood_(draw_likelihood) {
	initRandom();
}

Result Elo::determineResult(int r_A, int r_B, bool allow_draw) {
	double p = uniform_(rng_);
	if(allow_draw) {
		if(p < draw_likelihood_)
			return Result::Draw;
		else
			p = uniform_(rng_);
	}
	double win_A_likelihood = std::pow(1+std::pow(10, (r_B - r_A) / denominator_),-1);
	Result res = p < win_A_likelihood ? Result::Win : Result::Loss;
//	std::cout << "r_A = " << r_A << "; r_B = " << r_B << "; p(A) = " << win_A_likelihood << "; p_n = " << p << "; Result: " << resultToString(res) << std::endl;
	return res;
}

void Elo::initRandom() {
	std::random_device rd;
	rng_ = std::default_random_engine(rd());
}

Result invertResult(Result result) {
	switch(result) {
		case Result::Win:
			return Result::Loss;
		case Result::Loss:
			return Result::Win;
		default:
			return Result::Draw;
	}
	return Result::Draw;
}

int pointsFromResult(Result result) {
	switch(result) {
		case Result::Win:
			return 3;
		case Result::Loss:
			return 0;
		default:
			return 1;
	}
	return 1;
}

std::string resultToString(Result result) {
	switch(result) {
		case Result::Win:
			return "WIN";
		case Result::Loss:
			return "LOSS";
		default:
			return "DRAW";
	}
	return "DRAW";
}


}
