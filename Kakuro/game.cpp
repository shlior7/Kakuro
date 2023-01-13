#include "game.h"

//Improved Backtracking Solver
bool Game::solver(){
	solve_down(*(game_board->k_list.c_list.begin()));
	cout << "finished"<<endl;
	return false;
}
bool Game::solve_down(ptk_cell& k){
	if (k->d_list)
		for (auto& o : k->d_list->o_list.c_list)
		{
			auto n = o->possibilities.begin();
			if (!o->val)
				while (n != o->possibilities.end()){
					//if (possible(o->k_down, o->k_right, *n)) {
						o->fill(*n);
						if (!o->k_right->r_list->empty_cells && o->k_right->right_sum() != o->k_right->right() ||
							!o->k_down->d_list->empty_cells && o->k_down->down_sum() != o->k_down->down())
						{
							o->fill(0);
						}
						else {
							game_board->print();
							if (solve_right(o->k_right)) {
								//o->k_right->r_list->empty_list();
								o->fill(0);
							}

						}
					//}
					
					if (n != o->possibilities.end()) ++n;
				}
			if (!o->val|| o->min > o->max) {
				return true;
			}
		}
}

bool Game::solve_right(ptk_cell& k) {
	if (k->r_list)
		for (auto& o : k->r_list->o_list.c_list)
		{
			auto n = o->possibilities.begin();
			if (!o->val)
				while (n != o->possibilities.end()) {
					//if (possible(o->k_down, o->k_right, *n)) {
						o->fill(*n);
						if (!o->k_right->r_list->empty_cells && o->k_right->right_sum() != o->k_right->right() ||
							!o->k_down->d_list->empty_cells && o->k_down->down_sum() != o->k_down->down())
						{
							o->fill(0);

						}
						else {
							game_board->print();
							if (solve_down(o->k_down)) {
								o->fill(0);
								//o->k_down->d_list->empty_list();
							}
						}
					//}
					if(n != o->possibilities.end()) ++n;
				}
			if (!o->val|| o->min > o->max) {
				return true;
			}
		}
}
bool Game::possible(const ptk_cell& k_down,const ptk_cell& k_right,int n){

	if (n > k_down->d_list->remain()) return false;
	if (n > k_right->r_list->remain()) return false;
	if (!std::all_of(k_down->d_list->o_list.c_list.cbegin(), k_down->d_list->o_list.c_list.cend(),
		[n](auto& o) {return o->val != n; }))return false;
	if (!std::all_of(k_right->r_list->o_list.c_list.cbegin(), k_right->r_list->o_list.c_list.cend(),
		[n](auto& o) {return o->val != n; }))return false;
	return true;
}
