#include <tournament.h>

#include <algorithm>
#include <set>

namespace wmc_sim {

Tournament::Tournament(std::vector<Team> teams, Elo& elo) : teams_(teams), elo_(elo) {
	for(Team t : teams) {
		StandingPtr standing = std::make_shared<Standing>(t);
		standings_.push_back(*standing);
		team_results_[t] = standing;
	}

	std::random_device rd;
	rng_ = std::default_random_engine(rd());
}

void Tournament::perform() {
	//Three rounds swiss Sealed
	//Four rounds swiss Modern
	//Cut-off 48
	//First group phase
	//Second Group phase
	//top 8
}

void Tournament::sortStandings() {
	std::sort(standings_.begin(), standings_.end());
	std::reverse(standings_.begin(), standings_.end());
}

void Tournament::makePairings(std::vector<Pairing>& pairings, int min_round, int max_round) {
	sortStandings();

	std::map<int, std::pair<int, int>> point_groups_indices;
	std::vector<int> point_groups;
	std::vector<Team> teams_for_pairing;
	int curr_points = -1;
	int index = 0;
	int group_start_index = 0;
	for(Standing s : standings_) { 
		teams_for_pairing.push_back(s.team_);

		if(s.getPoints() != curr_points) {
			if(curr_points != -1) {
				point_groups.push_back(curr_points);
				point_groups_indices[curr_points] = std::pair<int, int>(group_start_index, index);
			}

			group_start_index = index;
			curr_points = s.getPoints();
		}

		++index;
	}

	// Shuffle each point group individually
	for(int points : point_groups) {
		shufflePart(teams_for_pairing, point_groups_indices[points].first, point_groups_indices[points].second);
	}

	// Build the actual pairings top down.
	std::set<Team> paired;
	for(int i = 0; i < teams_for_pairing.size(); ++i) {
		Team team_A = teams_for_pairing[i];
		if(paired.find(team_A) != paired.end())
			continue;
		Team team_B = teams_for_pairing[i]; //Useless initialization, because Team() doesn exist
		bool valid_pairing = false;
		int j = i;
		do {
			++j;
			if(j >= teams_for_pairing.size())
				break;
			team_B = teams_for_pairing[j];
			if(paired.find(team_B) != paired.end())
				continue;
			
			if(!havePlayedBefore(team_A, team_B, min_round, max_round))
				valid_pairing = true;
		} while(!valid_pairing);

		if(!valid_pairing) {
			Pairing p(team_A, boost::none, elo_);
			pairings.push_back(p);
		}
		else {
			Pairing p(team_A, team_B, elo_);
			pairings.push_back(p);
			paired.insert(team_B);
		}
		paired.insert(team_A);
	}

}

void Tournament::shufflePart(std::vector<Team>& list, int start_index, int end_index) {
	int end = std::min(end_index, int(list.size()));
	std::shuffle(list.begin()+start_index, list.begin()+end+1, rng_);
}

bool Tournament::havePlayedBefore(Team team_A, Team team_B, int min_round, int max_round) {
	for(int i = min_round; i <= max_round; ++i) {
		int round_index = i-1;
		if(*(opponents_per_round_[round_index][team_A]) == team_B)
			return true;
	}
	return false;
}

}
