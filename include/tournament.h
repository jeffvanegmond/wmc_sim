#pragma once
#include <team.h>
#include <elo.h>
#include <pairing.h>
#include <standing.h>

#include <memory>
#include <random>

namespace wmc_sim {

typedef std::shared_ptr<Standing> StandingPtr;

class Tournament {
public:
	Tournament(std::vector<Team> teams, Elo& elo);
	void perform();

private:

	void sortStandings();
	void makePairings(std::vector<Pairing>& pairings, int min_round, int max_round);
	void shufflePart(std::vector<Team>& list, int start_index, int end_index);
	bool havePlayedBefore(Team team_A, Team team_B, int min_round, int max_round);

	std::vector<Team> teams_;
	std::vector<Standing> standings_;
	std::map<Team, StandingPtr> team_results_;
	Elo elo_;

	std::vector<std::map<Team, boost::optional<Team>>> opponents_per_round_;

	std::default_random_engine rng_;
};

}
