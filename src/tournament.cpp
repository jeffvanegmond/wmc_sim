#include <tournament.h>

#include <algorithm>
#include <set>
#include <utility>

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
//		std::cout << "Team " << *t << " represent!" << std::endl;
	}

	//Three rounds swiss Sealed
	//Make team seatings
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition();
	}
	performSwissPart(1,3);
//	std::cout << "Done with first swiss part." << std::endl;

	//Four rounds swiss Modern
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition(t->composition[Seat::Coach]);
	}
	performSwissPart(4,7);
//	std::cout << "Done with the second swiss part." << std::endl;
//	printStandings();

	//Cut-off 48
	for(int i = 48; i < standings_.size(); ++i) {
		results[*(standings_[i]->team)] = FinalResult::NotTop48;
	}

	// Get back in best teamp comp
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition();
	}
	//First group phase
	// Make groups of 6;
	std::vector<SeededGroup> groups6;
	for(int i = 0; i < 8; ++i) {
		SeededGroup group;
		group.push_back(SeededTeam(0, standings_[     i]->team));
		group.push_back(SeededTeam(1, standings_[15 - i]->team));
		group.push_back(SeededTeam(2, standings_[16 + i]->team));
		group.push_back(SeededTeam(3, standings_[31 - i]->team));
		group.push_back(SeededTeam(4, standings_[32 + i]->team));
		group.push_back(SeededTeam(5, standings_[47 - i]->team));
		groups6.push_back(group);
	}
	std::vector<SeededGroup> groups4;
	for(auto group : groups6) {
		std::vector<Pairing> group_pairing;
		SeededGroup group4;

		Pairing p0{group[0].second, boost::none, elo_};
		playPairing(p0);
		group4.push_back(group[0]);

		Pairing p1{group[1].second, boost::none, elo_};
		playPairing(p1);
		group4.push_back(group[1]);

		Pairing p2{group[2].second, group[5].second, elo_};
		Result res2 = playPairing(p2);
		SeededTeam winner2 = res2 == Result::Win ? group[2] : group[5];
		SeededTeam loser2  = res2 == Result::Win ? group[5] : group[2];
		results[(*loser2.second)] = FinalResult::Top48;
		group4.push_back(winner2);

		Pairing p3{group[3].second, group[4].second, elo_};
		Result res3 = playPairing(p3);
		SeededTeam winner3 = res3 == Result::Win ? group[3] : group[4];
		SeededTeam loser3  = res3 == Result::Win ? group[4] : group[3];
		results[(*loser3.second)] = FinalResult::Top48;
		group4.push_back(winner3);

		std::sort(group4.begin(), group4.end());
		groups4.push_back(group4);
	}
	std::vector<Team> top16;
	performGroupPhase(groups4, top16, FinalResult::Top32);
	sortStandings();

	//Second Group phase
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition(t->composition[Seat::Coach]);
	}
	std::vector<StandingPtr> top16_standings;
	for(Team t : top16) {
		top16_standings.push_back(team_results_[t]);
	}
	std::sort(top16_standings.begin(), top16_standings.end(), compStandingPtr);
	std::reverse(top16_standings.begin(), top16_standings.end());

	groups4.clear();
	for(int i = 0; i < 4; ++i) {
		SeededGroup group;
		group.push_back(SeededTeam(0, top16_standings[     i]->team));
		group.push_back(SeededTeam(1, top16_standings[7  - i]->team));
		group.push_back(SeededTeam(2, top16_standings[8  + i]->team));
		group.push_back(SeededTeam(3, top16_standings[15 - i]->team));
		groups4.push_back(group);
	}
	std::vector<Team> top8;
	performGroupPhase(groups4, top8, FinalResult::Top16);
	sortStandings();

	//top 8
	for(TeamPtr t : teams_) {
		t->makeStrongestComposition();
	}
	std::vector<StandingPtr> top8_standings;
	for(Team t : top8) {
		top8_standings.push_back(team_results_[t]);
	}
	std::sort(top8_standings.begin(), top8_standings.end(), compStandingPtr);
	std::reverse(top8_standings.begin(), top8_standings.end());

	std::vector<TeamPtr> top4;
	for(int i = 0; i < 4; ++i) {
		Pairing q{top8_standings[i]->team, top8_standings[7-i]->team, elo_};
		Result res = playPairing(q);
		TeamPtr winner = res == Result::Win ? top8_standings[i]->team : top8_standings[7-i]->team;
		TeamPtr loser  = res == Result::Win ? top8_standings[7-i]->team : top8_standings[i]->team;
		results[*loser] = FinalResult::Top8;
		top4.push_back(winner);
	}

	std::vector<TeamPtr> finals;
	for(int i = 0; i < 2; ++i) {
		Pairing s{top4[i], top4[3-i], elo_};
		Result res = playPairing(s);
		TeamPtr winner = res == Result::Win ? top4[i] : top4[3-i];
		TeamPtr loser  = res == Result::Win ? top4[3-i] : top4[i];
		results[*loser] = FinalResult::Top4;
		finals.push_back(winner);
	}

	Pairing f{finals[0], finals[1], elo_};
	Result res = playPairing(f);
	TeamPtr winner = res == Result::Win ? finals[0] : finals[1];
	TeamPtr loser  = res == Result::Win ? finals[1] : finals[0];
	results[*winner] = FinalResult::First;
	results[*loser]  = FinalResult::Second;

//	printResults();
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
//		std::cout << "=== Pairings round " << round << std::endl;
		std::map<Team, boost::optional<TeamPtr>> paired_against;
		for(Pairing p : pairings) {
			paired_against[*(p.team_A)] = p.team_B;
			if(p.team_B != boost::none) {
				paired_against[**(p.team_B)] = p.team_A;
			}
			Result result = playPairing(p);
		}

		opponents_per_round_.push_back(paired_against);
		sortStandings();
//		std::cout << "Round " << round << " in the books!" << std::endl;
//		printStandings();
	}
}

Result Tournament::playPairing(Pairing& pairing) {
	Result result = pairing.getResult();

	StandingPtr standing_A = team_results_[*(pairing.team_A)];
	StandingPtr standing_B;
	if(pairing.team_B != boost::none) {
		standing_B = team_results_[**(pairing.team_B)];
		standing_B->addResult(standing_A, invertResult(result));
		standing_A->addResult(standing_B, result);
	}
	else {
		standing_A->addResult(boost::none, result);
	}

	return result;
}

void Tournament::printResults() {
	int i = 0;
	std::cout << "=== Printing all results" << std::endl;
	std::map<FinalResult, int> sanity_check;
	for(int i = 0; i <= int(FinalResult::NotTop48); ++i) {
		sanity_check[FinalResult(i)] = 0;
	}
	for(auto iterator = results.begin(); iterator!= results.end(); iterator++) {
		std::cout << ++i << ". Team " << iterator->first << " got " << finalResultToString(iterator->second) << std::endl;
		sanity_check[iterator->second] += 1;
	}
	std::cout << "Printing sanity check:" << std::endl;
	for(int i = 0; i <= int(FinalResult::NotTop48); ++i) {
		std::cout << sanity_check[FinalResult(i)] << " finished with result " << finalResultToString(FinalResult(i)) << std::endl;
	}
}

void Tournament::performGroupPhase(std::vector<SeededGroup>& groups4, std::vector<Team>& topX, FinalResult elim_res) {
	for(SeededGroup& group : groups4) {
		Pairing p0{group[0].second, group[3].second, elo_};
		Result res0 = playPairing(p0);
		SeededTeam winner0 = res0 == Result::Win ? group[0] : group[3];
		SeededTeam loser0  = res0 == Result::Win ? group[3] : group[0];

		Pairing p1{group[1].second, group[2].second, elo_};
		Result res1 = playPairing(p1);
		SeededTeam winner1 = res1 == Result::Win ? group[1] : group[2];
		SeededTeam loser1  = res1 == Result::Win ? group[2] : group[1];

		Pairing p2{winner0.second, winner1.second, elo_};
		Result res2 = playPairing(p2);
		SeededTeam winner2 = res2 == Result::Win ? winner0 : winner1;
		SeededTeam loser2  = res2 == Result::Win ? winner1 : winner0;

		Pairing p3{loser0.second, loser1.second, elo_};
		Result res3 = playPairing(p3);
		SeededTeam winner3 = res3 == Result::Win ? loser0 : loser1;
		SeededTeam loser3  = res3 == Result::Win ? loser1 : loser0;
		results[*(loser3.second)] = elim_res;

		Pairing p4{winner2.second, boost::none, elo_};
		playPairing(p4);
		topX.push_back(*(winner2.second));

		Pairing p5{loser2.second, winner3.second, elo_};
		Result res5 = playPairing(p5);
		SeededTeam winner5 = res5 == Result::Win ? loser2  : winner3;
		SeededTeam loser5  = res5 == Result::Win ? winner3 : loser2;
		topX.push_back(*(winner5.second));
		results[*(loser5.second)] = elim_res;
	}
}

std::string finalResultToString(FinalResult result) {
	switch(result) {
		case FinalResult::First:
			return "FIRST";
		case FinalResult::Second:
			return "SECOND";
		case FinalResult::Top4:
			return "Top4";
		case FinalResult::Top8:
			return "Top8";
		case FinalResult::Top16:
			return "Top16";
		case FinalResult::Top32:
			return "Top32";
		case FinalResult::Top48:
			return "Top48";
		default:
			return "NotTop48";
	}
	return "NotTop48";
}

}
