#include "game.h"

bool Game::solver()
{
	for (auto &k : game_board->k_list.c_list)
	{
		//	cout << "K: " << k->down <<"  "<<k->right<<endl;
		if (k->d_list)
			for (auto &o : k->d_list->o_list.c_list)
			{
				//	cout << "o down: " << o->val << " x,y: " << o->x << " ," << o->y << endl;
				if (!o->val)
					for (int n = 1; n < 10; n++)
						if (possible(o->k_down, o->k_right, n))
						{
							o->val = n;
							o->k_down->d_list->add_to_sum(n);
							if (o->k_right)
								o->k_right->r_list->add_to_sum(n);
							//	cout <<endl<< "o down: " << o->val << " x,y: " << o->x << " ," << o->y << endl;
							// cout << "try Val: "<< n<<endl;
							// game_board->print();
							if (solver())
							{
								o->val = 0;
								o->k_down->d_list->add_to_sum(-n);
								if (o->k_right)
									o->k_right->r_list->add_to_sum(-n);
							}
							else
								return false;
						}
				if (!o->val)
					return true;
			}
		if (k->down_sum() != k->down())
			return true;
		if (k->r_list)
			for (auto &o : k->r_list->o_list.c_list)
			{
				//	cout << "o right: " << o->val <<" x,y: "<<o->x<<" ,"<<o->y<<endl;
				if (!o->val)
					for (int n = 1; n < 10; n++)
						if (possible(o->k_down, o->k_right, n))
						{
							o->val = n;
							o->k_right->r_list->add_to_sum(n);
							if (o->k_down)
								o->k_down->d_list->add_to_sum(n);
							//	cout << endl << "o right: " << o->val << " x,y: " << o->x << " ," << o->y << endl;
							//		cout << "try Val: " << n<<endl;
							// game_board->print();
							if (solver())
							{
								o->val = 0;
								o->k_right->r_list->add_to_sum(-n);
								if (o->k_down)
									o->k_down->d_list->add_to_sum(-n);
							}
							else
								return false;
						}
				if (!o->val)
					return true;
			}
		if (k->right_sum() != k->right())
			return true;
	}
	// game_board->print();
	// cout << "finished"<<endl;
	return false;
}

bool Game::possible(const ptk_cell &k_down, const ptk_cell &k_right, int n)
{

	if (n > k_down->d_list->max || n < k_down->d_list->min)
		return false;
	if (n > k_right->r_list->max || n < k_right->r_list->min)
		return false;
	if (n > k_down->d_list->remain())
		return false;
	if (n > k_right->r_list->remain())
		return false;
	if (!std::all_of(k_down->d_list->o_list.c_list.cbegin(), k_down->d_list->o_list.c_list.cend(),
									 [n](auto &o)
									 { return o->val != n; }))
		return false;
	if (!std::all_of(k_right->r_list->o_list.c_list.cbegin(), k_right->r_list->o_list.c_list.cend(),
									 [n](auto &o)
									 { return o->val != n; }))
		return false;
	return true;
}
