#include <fstream>
#include "game.h"

int main()
{
	std::vector<std::vector<int>> example = {
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
	Game kakuro(example);
	// ifstream in;
	// in.open("kakuro1.txt");
	// kakuro.game_board->get_board(cin);
	// in.close();
	kakuro.game_board->toVector();
	printf("wow");
	kakuro.solver();
	kakuro.game_board->print();
}
