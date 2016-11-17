#include <pairing.h>

namespace wmc_sim {

Pairing::Pairing(TeamPtr team_A, boost::optional<TeamPtr> team_B, Elo* elo)
               : team_A(team_A), team_B(team_B), elo_(elo) {}

Result Pairing::getResult() {
	if(team_B == boost::none)
		return Result::Win;
	int wins = 0;
	int losses = 0;
	for(int i = 0; i < 3; ++i) {
		Seat seat = Seat(i);
		Player player_A = team_A->composition[seat];
		int elo_A = team_A->elo_ratings[player_A];
		Player player_B = (*team_B)->composition[seat];
		int elo_B = (*team_B)->elo_ratings[player_B];
//		std::cout << "Seat " << seatToString(seat) << " has player " << playerToString(player_A) << " vs player " << playerToString(player_B) << std::endl;
		Result match_result = elo_->determineResult(elo_A, elo_B);

		if(match_result == Result::Win)
			++wins;
		if(match_result == Result::Loss)
			++losses;
	}
	if(wins == losses)
		return Result::Draw;
	return wins > losses ? Result::Win : Result::Loss;
}

}
