#pragma once
#include <elo.h>
#include <team.h>

#include <map>
#include <memory>
#include <boost/optional.hpp>
#include <iostream>

namespace wmc_sim {

class Standing;
typedef std::shared_ptr<Standing> StandingPtr;

class Standing {
public:
	Standing(TeamPtr team);

	int getPoints();
	double getResistance() const;
	void addResult(boost::optional<StandingPtr> opp, Result result);

	friend bool operator==(const Standing& lhs, const Standing& rhs);
	friend bool operator<(const Standing& lhs, const Standing& rhs);
	friend std::ostream& operator<<(std::ostream& out, const Standing& rhs);

	TeamPtr team;

private:
	int points_;
	int rounds_played_;
	
	std::vector<boost::optional<StandingPtr>> opponents_;
	std::vector<Result> results_;
};

bool compStandingPtr(const StandingPtr a, const StandingPtr b);

}
