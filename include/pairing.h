#pragma once
#include <team.h>
#include <elo.h>
#include <boost/optional.hpp>

namespace wmc_sim {

class Pairing {
public:
	Pairing(TeamPtr team_A, boost::optional<TeamPtr> team_B, Elo* elo);
	Result getResult();

	TeamPtr team_A;
	boost::optional<TeamPtr> team_B;
private:
	Elo* elo_;
};

}
