#pragma once
#include <team.h>
#include <elo.h>
#include <pairing.h>
#include <standing.h>

#include <random>

namespace wmc_sim {


class Tournament {
public:
	Tournament(std::vector<Team> teams, Elo* elo);
	void perform();

private:

	void sortStandings();
	void printStandings();
	void makePairings(std::vector<Pairing>& pairings, int min_round, int max_round);
	void shufflePart(std::vector<TeamPtr>& list, int start_index, int end_index);
	bool havePlayedBefore(Team team_A, Team team_B, int min_round, int max_round);

	void performSwissPart(int start_round, int end_round);

	std::vector<TeamPtr> teams_;
	std::vector<StandingPtr> standings_;
	std::map<Team, StandingPtr> team_results_;
	Elo* elo_;

	std::vector<std::map<Team, boost::optional<TeamPtr>>> opponents_per_round_;

	std::default_random_engine rng_;
};

}
