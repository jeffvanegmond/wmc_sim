#include <team.h>

namespace wmc_sim {

Team::Team(std::string country, int ratings[4]) : country_(country) {
	for(int i = 0; i < 4; ++i) {
		elo_ratings[Player(i)] = ratings[i];
	}
	initRandom();
}

void Team::makeStrongestComposition() {
}

void Team::makeStrongestComposition(Player required_player) {
}

bool operator==(const Team& lhs, const Team& rhs) {
	return lhs.country_ == rhs.country_;
}

bool operator<(const Team& lhs, const Team& rhs) {
	return lhs.country_ < rhs.country_;
}

void Team::initRandom() {
	std::random_device rd;
	rng_ = std::default_random_engine(rd());
}

void Team::randomizeSeating(Player coach) {
	composition[Seat::Coach] = coach;
	for(int i = 0; i < 3; ++i) {
		Seat seat = Seat(i);
		Player player;
		bool seated = false;
		do {
			player = randomPlayer();
			for(int j = i-1; j >=0; --j) {
				if(composition[Seat(j)] == player)
					seated = true;
			}
		} while(player == coach && seated);
		composition[seat] = player;
	}
}

Player Team::randomPlayer() {
	int number = uniform_distribution_(rng_);
	return Player(number);
}

}
