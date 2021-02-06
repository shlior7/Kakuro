#include <fstream>
#include "game.h"

int main(){
	
	Game kakuro(7, 7);
	ifstream in;
	in.open("kakuro1.txt");
	kakuro.game_board->get_board(cin);
	in.close();
	kakuro.game_board->print();

	kakuro.solver();
	kakuro.game_board->print();
}
