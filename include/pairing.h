#pragma once
#include <team.h>
#include <elo.h>
#include <boost/optional.hpp>

namespace wmc_sim {

class Pairing {
public:
	Pairing(Team team_A, boost::optional<Team> team_B, Elo& elo);
	Result getResult();

	Team team_A;
	boost::optional<Team> team_B;
private:
	Elo elo_;
};

}
