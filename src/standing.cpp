#include <standing.h>

#include <algorithm>

namespace wmc_sim {

Standing::Standing(TeamPtr team) : team(team), points_(0), rounds_played_(0) {}

int Standing::getPoints() {
	return points_;
}

double Standing::getResistance() const {
	// Based on http://www.wizards.com/dci/downloads/tiebreakers.pdf
	double resistance = 0.0;
	int non_byes = 0;
	for(boost::optional<StandingPtr> opp : opponents_) {
		if(opp == boost::none)
			continue;

		double omw = std::max(0.33, (*opp)->points_ / (3.0 * (*opp)->rounds_played_));
		resistance += omw;
		++non_byes;
	}
	if(non_byes == 0)
		return 0;
	return resistance / non_byes;
}

void Standing::addResult(boost::optional<StandingPtr> opp, Result result) {
	points_ += pointsFromResult(result);
	++rounds_played_;
	results_.push_back(result);
	opponents_.push_back(opp);
}

bool operator==(const Standing& lhs, const Standing& rhs) {
	return *(lhs.team) == *(rhs.team);
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
	return *(lhs.team) < *(rhs.team); // Yes, this is stupid, but this is the fallback in case of a tie in OMW, it puts the teams in alphabetical order
}

std::ostream& operator<<(std::ostream& out, const Standing& rhs) {
	return out << *(rhs.team) << " " << rhs.points_ << "pts OMW: " << rhs.getResistance();
}

bool compStandingPtr(const StandingPtr a, const StandingPtr b) {
	return (*a) < (*b);
}

}
