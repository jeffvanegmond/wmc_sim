#pragma once
#include <team.h>
#include <elo.h>
#include <pairing.h>
#include <standing.h>

#include <random>

namespace wmc_sim {

enum class FinalResult {First, Second, Top4, Top8, Top16, Top32, Top48, NotTop48};
std::string finalResultToString(FinalResult result);

typedef std::pair<int, TeamPtr> SeededTeam;
typedef std::vector<SeededTeam> SeededGroup;

class Tournament {
public:
	Tournament(std::vector<Team> teams, Elo* elo);
	void perform();

	std::map<Team, FinalResult> results;

private:

	void sortStandings();
	void printStandings();
	void printResults();
	void makePairings(std::vector<Pairing>& pairings, int min_round, int max_round);
	void shufflePart(std::vector<TeamPtr>& list, int start_index, int end_index);
	bool havePlayedBefore(Team team_A, Team team_B, int min_round, int max_round);

	void performSwissPart(int start_round, int end_round);
	void performGroupPhase(std::vector<SeededGroup>& groups4, std::vector<Team>& topX, FinalResult elim_res);
	Result playPairing(Pairing& pairing);

	std::vector<TeamPtr> teams_;
	std::vector<StandingPtr> standings_;
	std::map<Team, StandingPtr> team_results_;
	Elo* elo_;

	std::vector<std::map<Team, boost::optional<TeamPtr>>> opponents_per_round_;

	std::default_random_engine rng_;
};

}
