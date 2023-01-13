#include "board.h"

class Game
{
public:
	unique_ptr<board> game_board;
	Game(int width, int height) :game_board(make_unique<board>(width, height)) {}
	bool solver();
	bool solve_down(ptk_cell& k);
	bool solve_right(ptk_cell& k);
	bool possible(const ptk_cell& k_down, const ptk_cell& k_right, int n);
	void calculate_options(set<int> curent, int n, int k);
};