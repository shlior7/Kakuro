#include "board.h"

class Game
{
public:
	// const int SUM[] = { 0,1,3,6,10,15,21,28,36,45 };
	unique_ptr<board> game_board;
	Game(int width, int height) : game_board(make_unique<board>(width, height)) {}
	Game(std::vector<std::vector<int>> mat) : game_board(make_unique<board>(mat)) {}
	bool solver(bool v);
	bool solve_vertical(sum_cell_ptr b);
	bool solve_horizontal(sum_cell_ptr b);
	bool possible(const shared_ptr<sum_cell> &k_down, const shared_ptr<sum_cell> &k_right, int n);
	bool validate();
};
