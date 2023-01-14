#include <fstream>
#include "game.h"

int main()
{
	std::vector<std::vector<int>> example1 = {
			{
					-1,
					-1,
					-1,
					-1,
					4,
					0,
					10,
					0,
					-1,
					-1,
					-1,
					-1,
					-1,
					-1,
			},
			{
					-1,
					-1,
					0,
					4,
					0,
					0,
					0,
					0,
					-1,
					-1,
					3,
					0,
					4,
					0,
			},
			{
					-1,
					-1,
					0,
					3,
					0,
					0,
					0,
					0,
					11,
					4,
					0,
					0,
					0,
					0,
			},
			{
					-1,
					-1,
					3,
					0,
					4,
					10,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
			},
			{
					0,
					11,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					4,
					0,
					-1,
					-1,
			},
			{
					0,
					4,
					0,
					0,
					0,
					0,
					0,
					4,
					0,
					0,
					0,
					0,
					-1,
					-1,
			},
			{
					-1,
					-1,
					-1,
					-1,
					-1,
					-1,
					0,
					3,
					0,
					0,
					0,
					0,
					-1,
					-1,
			},
	};

	std::vector<std::vector<int>> example2 = {
			{-1, -1, 3, -1, 11, -1, -1,
			 -1, -1, -1, 4, -1, 15, -1,
			 -1, -1, -1, -1},
			{-1, 8, 0, 0, 0, 0, 4,
			 -1, -1, 3, 0, 0, 0, 0,
			 30, -1, 18, -1},
			{-1, 7, 0, 0, 0, 0, 0,
			 0, 7, 14, 0, 0, 0, 0,
			 0, 0, 0, 0},
			{-1, -1, 25, -1, 27, 4, 0,
			 0, 0, 0, 6, 24, 0, 0,
			 0, 0, 0, 0},
			{-1, 17, 0, 0, 0, 0, 29,
			 16, 0, 0, 0, 0, 0, 0,
			 0, 0, 0, 0},
			{-1, 15, 0, 0, 0, 0, 0,
			 0, 0, 0, 0, 0, 3, 16,
			 0, 0, 0, 0},
			{-1, 24, 0, 0, 0, 0, 0,
			 0, 17, 4, 0, 0, 0, 0,
			 4, -1, 3, -1},
			{-1, 29, 0, 0, 0, 0, 0,
			 0, 0, 0, -1, 6, 0, 0,
			 0, 0, 0, 0},
			{-1, -1, -1, -1, -1, 16, 0,
			 0, 0, 0, -1, -1, -1, 3,
			 0, 0, 0, 0} };

	Game kakuro(example2);
	// ifstream in;
	// in.open("kakuro1.txt");
	// kakuro.gameBoard->get_board(cin);
	// in.close();
	kakuro.game_board->toVector();
	// printf("wow");
	kakuro.solver();
	kakuro.game_board->print();
}
