#include <standing.h>

#include <algorithm>

namespace wmc_sim {

Standing::Standing(Team team) : team_(team), points_(0), rounds_played_(0) {}

int Standing::getPoints() {
	return points_;
}

double Standing::getResistance() const {
	// Based on http://www.wizards.com/dci/downloads/tiebreakers.pdf
	double resistance = 0.0;
	int non_byes = 0;
	for(boost::optional<Standing*> opp : opponents_) {
		if(opp == boost::none)
			continue;

		double omw = std::min(0.33, (*opp)->points_ / (3.0 * (*opp)->rounds_played_));
		resistance += omw;
		++non_byes;
	}
	return resistance / non_byes;
}

void Standing::addResult(boost::optional<Standing*> opp, Result result) {
	points_ += pointsFromResult(result);
	++rounds_played_;
	results_.push_back(result);
	opponents_.push_back(opp);
}

bool operator==(const Standing& lhs, const Standing& rhs) {
	return lhs.team_ == rhs.team_;
}

bool operator<(const Standing& lhs, const Standing& rhs) {
	if(lhs.rounds_played_ != rhs.rounds_played_)
		return lhs.rounds_played_ < rhs.rounds_played_;
	if(lhs.points_ != rhs.points_)
		return lhs.points_ < rhs.points_;
	double lhs_resistance = lhs.getResistance();
	double rhs_resistance = rhs.getResistance();
	if(lhs_resistance != rhs_resistance)
		return lhs_resistance < rhs_resistance;
	return rhs.team_ < lhs.team_; // Yes, this is stupid, but this is the fallback in case of a tie in OMW, it puts the teams in alphabetical order
}

}
