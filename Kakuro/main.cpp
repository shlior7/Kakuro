#include <fstream>
#include "game.h"

int main()
{

	Game kakuro(7, 7);
	ifstream in;
	//.open("kakuro1.txt");
	kakuro.game_board->get_board(cin);
	// in.close();
	kakuro.game_board->print();
	try
	{
		kakuro.solver();
	}
	catch (...)
	{
		cout << "no Solution\n";
	}
	kakuro.game_board->print();
}
