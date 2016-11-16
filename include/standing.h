#pragma once
#include <elo.h>
#include <team.h>

#include <map>
#include <boost/optional.hpp>

namespace wmc_sim {

class Standing {
public:
	Standing(Team team);

	int getPoints();
	double getResistance() const;
	void addResult(boost::optional<Standing*> opp, Result result);

	friend bool operator==(const Standing& lhs, const Standing& rhs);
	friend bool operator<(const Standing& lhs, const Standing& rhs);

	Team team_;

private:
	int points_;
	int rounds_played_;
	
	std::vector<boost::optional<Standing*>> opponents_;
	std::vector<Result> results_;
};

}
