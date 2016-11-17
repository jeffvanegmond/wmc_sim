#include <tournament.h>

#include <algorithm>
#include <set>

namespace wmc_sim {

Tournament::Tournament(std::vector<Team> teams, Elo* elo) : elo_(elo) {
	for(Team t : teams) {
		TeamPtr tptr = std::make_shared<Team>(t);
		StandingPtr standing = std::make_shared<Standing>(tptr);
		standings_.push_back(standing);
		team_results_[t] = standing;
		teams_.push_back(tptr);
	}

	std::random_device rd;
	rng_ = std::default_random_engine(rd());
}

void Tournament::perform() {
	//For testing: output teams
	for(TeamPtr t : teams_) {
		std::cout << "Team " << *t << " represent!" << std::endl;
	}

	//Three rounds swiss Sealed
	//Make team seatings
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition();
	}
	performSwissPart(1,3);
	std::cout << "Done with first part..." << std::endl;

	//Four rounds swiss Modern
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition(t->composition[Seat::Coach]);
	}
	performSwissPart(4,7);
	std::cout << "Done with the second swiss part." << std::endl;
	//Cut-off 48
	//First group phase
	//Second Group phase
	//top 8
}

void Tournament::sortStandings() {
//	std::cout << "Sorting standings." << std::endl;
	std::sort(standings_.begin(), standings_.end(), compStandingPtr);
//	std::cout << "Reversing standings." << std::endl;
	std::reverse(standings_.begin(), standings_.end());
}

void Tournament::printStandings() {
	int position = 1;
	for(const StandingPtr s : standings_) {
		std::cout << position << ". " << *s << std::endl;
		++position;
	}
}

void Tournament::makePairings(std::vector<Pairing>& pairings, int min_round, int max_round) {
//	std::cout << "Making pairings" << std::endl;
	std::map<int, std::pair<int, int>> point_groups_indices;
	std::vector<int> point_groups;
	std::vector<TeamPtr> teams_for_pairing;
	int curr_points = -1;
	int index = 0;
	int group_start_index = 0;
	for(StandingPtr s : standings_) {
		teams_for_pairing.push_back(s->team);

		if(s->getPoints() != curr_points) {
			if(curr_points != -1) {
				point_groups.push_back(curr_points);
				point_groups_indices[curr_points] = std::pair<int, int>(group_start_index, index - 1);
//				std::cout << "  Group starts with index " << group_start_index << " and ends with " << index-1 << std::endl;
			}

//			std::cout << "Found group with " << s->getPoints() << " points" << std::endl;
			group_start_index = index;
			curr_points = s->getPoints();
		}

		++index;
	}
	point_groups.push_back(curr_points);
	point_groups_indices[curr_points] = std::pair<int, int>(group_start_index, index-1);
//	std::cout << "  Group starts with index " << group_start_index << " and ends with " << index-1 << std::endl;

	// Shuffle each point group individually
	for(int points : point_groups) {
//		std::cout << "Shuffling teams with " << points << " points" << std::endl;
		shufflePart(teams_for_pairing, point_groups_indices[points].first, point_groups_indices[points].second);
	}

//	std::cout << "Start building pairings from the top down." << std::endl;
	// Build the actual pairings top down.
	std::set<Team> paired;
	for(int i = 0; i < teams_for_pairing.size(); ++i) {
		TeamPtr team_A = teams_for_pairing[i];
//		std::cout << "  Trying to find a pairing for " << team_A << std::endl;
		if(paired.find(*team_A) != paired.end()) {
//			std::cout << "    This team was already paired, next please!" << std::endl;
			continue;
		}
		TeamPtr team_B = teams_for_pairing[i]; //Useless initialization, because Team() doesn exist
		bool valid_pairing = false;
		int j = i;
		do {
			++j;
			if(j >= teams_for_pairing.size()) {
//				std::cout << "    No viable pairing left for this team, here's a BYE" << std::endl;
				break;
			}
			team_B = teams_for_pairing[j];
//			std::cout << "    Evaluating " << team_B << " as a candidate opponent." << std::endl;
			if(paired.find(*team_B) != paired.end()) {
//				std::cout << "      This team was already paired, next please!" << std::endl;
				continue;
			}
			
			if(!havePlayedBefore(*team_A, *team_B, min_round, max_round)) {
//				std::cout << "      Valid pairing!" << std::endl;
				valid_pairing = true;
			}
			else {
//				std::cout << "      These teams have already played against each other." << std::endl;
			}
		} while(!valid_pairing);

		if(!valid_pairing) {
//			std::cout << "    Adding a BYE" << std::endl;
			Pairing p(team_A, boost::none, elo_);
			pairings.push_back(p);
		}
		else {
//			std::cout << "    Pairing: " << team_A << " vs " << team_B << std::endl;
			Pairing p(team_A, team_B, elo_);
			pairings.push_back(p);
			paired.insert(*team_B);
		}
		paired.insert(*team_A);
	}

}

void Tournament::shufflePart(std::vector<TeamPtr>& list, int start_index, int end_index) {
	int end = std::min(end_index, int(list.size()));
	std::shuffle(list.begin()+start_index, list.begin()+end+1, rng_);
}

bool Tournament::havePlayedBefore(Team team_A, Team team_B, int min_round, int max_round) {
	max_round = std::min(max_round, int(opponents_per_round_.size()) + 1);
//	std::cout << "      Checking if these teams have played before between rounds " << min_round << " and " << max_round << "."  << std::endl;
	for(int i = min_round; i < max_round; ++i) {
//		std::cout << "        Evaluating round " << i << std::endl;
		int round_index = i-1;
		if(opponents_per_round_[round_index][team_A] != boost::none &&
			**(opponents_per_round_[round_index][team_A]) == team_B)
			return true;
	}
	return false;
}

void Tournament::performSwissPart(int start_round, int end_round) {

	std::vector<Pairing> pairings;
	for(int round = start_round; round <= end_round; ++round) {
		pairings.clear();
		makePairings(pairings, 1, round);
		std::cout << "=== Pairings round " << round << std::endl;
		std::map<Team, boost::optional<TeamPtr>> paired_against;
		for(Pairing p : pairings) {
			Result result = p.getResult();

			paired_against[*(p.team_A)] = p.team_B;
			int points_before_round_A, points_before_round_B;
			StandingPtr standing_A = team_results_[*(p.team_A)];
			points_before_round_A = standing_A->getPoints();
			StandingPtr standing_B;
			if(p.team_B != boost::none) {
				paired_against[**(p.team_B)] = p.team_A;
				standing_B = team_results_[**(p.team_B)];
				points_before_round_B = standing_B->getPoints();
				standing_B->addResult(standing_A, invertResult(result));
				standing_A->addResult(standing_B, result);
			}
			else {
				standing_A->addResult(boost::none, result);
			}

			std::cout << *(p.team_A) << "(" << points_before_round_A << ") vs ";
			if(p.team_B != boost::none) {
				std::cout << **(p.team_B) << "(" << points_before_round_B << ")";
			} else {
				std::cout << "BYE";
			}
			std::cout << " ===== " << resultToString(result) << std::endl;
		}

		opponents_per_round_.push_back(paired_against);
		sortStandings();
		std::cout << "Round " << round << " in the books!" << std::endl;
		printStandings();
	}
}

}
