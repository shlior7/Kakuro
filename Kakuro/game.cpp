#include "game.h"

bool Game::solver()
{
	for (auto &block : game_board->sum_cells.the_list)
	{
		//	cout << "K: " << k->down <<"  "<<k->right<<endl;
		if (block->vertical_block)
			for (auto &n_cell : block->vertical_block->numbersBlock.the_list)
			{
				//	cout << "n_cell down: " << n_cell->val << " x,y: " << n_cell->x << " ," << n_cell->y << endl;
				if (!n_cell->val)
					for (int n = 1; n < 10; n++)
						if (possible(n_cell->v_sum_cell, n_cell->h_sum_cell, n))
						{
							n_cell->val = n;
							n_cell->v_sum_cell->vertical_block->add_to_sum(n);
							if (n_cell->h_sum_cell)
								n_cell->h_sum_cell->horizontal_block->add_to_sum(n);
							//	cout <<endl<< "n_cell down: " << n_cell->val << " x,y: " << n_cell->x << " ," << n_cell->y << endl;
							// cout << "try Val: "<< n<<endl;
							// gameBoard->print();
							if (solver())
							{
								n_cell->val = 0;
								n_cell->v_sum_cell->vertical_block->add_to_sum(-n);
								if (n_cell->h_sum_cell)
									n_cell->h_sum_cell->horizontal_block->add_to_sum(-n);
							}
							else
								return false;
						}
				if (!n_cell->val)
					return true;
			}
		if (block->down_sum() != block->down())
			return true;

		if (block->horizontal_block)
			for (auto &n_cell : block->horizontal_block->numbersBlock.the_list)
			{
				//	cout << "n_cell right: " << n_cell->val <<" x,y: "<<n_cell->x<<" ,"<<n_cell->y<<endl;
				if (!n_cell->val)
					for (int n = 1; n < 10; n++)
						if (possible(n_cell->v_sum_cell, n_cell->h_sum_cell, n))
						{
							n_cell->val = n;
							n_cell->h_sum_cell->horizontal_block->add_to_sum(n);
							if (n_cell->v_sum_cell)
								n_cell->v_sum_cell->vertical_block->add_to_sum(n);
							//	cout << endl << "n_cell right: " << n_cell->val << " x,y: " << n_cell->x << " ," << n_cell->y << endl;
							//		cout << "try Val: " << n<<endl;
							// gameBoard->print();
							if (solver())
							{
								n_cell->val = 0;
								n_cell->h_sum_cell->horizontal_block->add_to_sum(-n);
								if (n_cell->v_sum_cell)
									n_cell->v_sum_cell->vertical_block->add_to_sum(-n);
							}
							else
								return false;
						}
				if (!n_cell->val)
					return true;
			}
		if (block->right_sum() != block->right())
			return true;
	}
	// gameBoard->print();
	// cout << "finished"<<endl;
	return false;
}

bool Game::possible(const sum_cell_ptr &v_sum_cell, const sum_cell_ptr &h_sum_cell, int n)
{

	if (n > v_sum_cell->vertical_block->max || n < v_sum_cell->vertical_block->min)
		return false;
	if (n > h_sum_cell->horizontal_block->max || n < h_sum_cell->horizontal_block->min)
		return false;
	if (n > v_sum_cell->vertical_block->remain())
		return false;
	if (n > h_sum_cell->horizontal_block->remain())
		return false;
	if (!std::all_of(v_sum_cell->vertical_block->numbersBlock.the_list.cbegin(), v_sum_cell->vertical_block->numbersBlock.the_list.cend(),
									 [n](auto &n_cell)
									 { return n_cell->val != n; }))
		return false;
	if (!std::all_of(h_sum_cell->horizontal_block->numbersBlock.the_list.cbegin(), h_sum_cell->horizontal_block->numbersBlock.the_list.cend(),
									 [n](auto &n_cell)
									 { return n_cell->val != n; }))
		return false;
	return true;
}
