#include "board.h"

class Game
{
public:
	//const int SUM[] = { 0,1,3,6,10,15,21,28,36,45 };
	unique_ptr<board> game_board;
	Game(int width,int height):game_board(make_unique<board>(width, height)) {}
	bool solver();
	bool solve_down(shared_ptr<k_cell>& k);
	bool solve_right();
	bool possible(const shared_ptr<k_cell>& k_down,const shared_ptr<k_cell>& k_right, int n);
};