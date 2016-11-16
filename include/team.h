#pragma once
#include <random>
#include <map>
#include <string>

namespace wmc_sim {

enum class Player{A,B,C,D};
enum class Seat{A,B,C,Coach};
class Team {
public:
	Team(std::string country, int ratings[4]);

	void makeStrongestComposition();
	void makeStrongestComposition(Player required_player);

	friend bool operator==(const Team& lhs, const Team& rhs);
	friend bool operator<(const Team& lhs, const Team& rhs);

	std::map<Seat, Player> composition;
	std::map<Player, int> elo_ratings;

private:
	void initRandom();
	void randomizeSeating(Player coach);
	Player randomPlayer();

	std::default_random_engine rng_;
	std::uniform_int_distribution<> uniform_distribution_{0,3};

	std::string country_;
};

}
