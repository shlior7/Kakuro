#include "board.h"
enum type
{
	null_cell_type = -1,
	o_cell_type = 0,
	k_cell_type = 1
};
void board::get_board(istream& in){
	string cur1,cur2;
	int c1, c2;
	in >> width >> height;
	for (auto j = 0;j < height;++j)
	{
		for (auto i = 0; i < width; ++i)
		{
			cout << i << " " << j<<endl;
			in >> cur1;
			in >> cur2;
			if (cur1 == "-")
				c1 = -1;
			else
				c1 = std::stoi(cur1);
			if (cur2 == "-")
				c2 = -1;
			else
				c2 = std::stoi(cur2);
			push_current(c1, c2, i, j);
		}
	}
	//print();
	connectLists();
}

void board::push_current(int cur1,int cur2,int i,int j){
	type cell_type;
	if (cur1 == -1 && cur2 == -1)
		cell_type = null_cell_type;
	else if (!cur1 && !cur2)
		cell_type = o_cell_type;
	else
		cell_type = k_cell_type;

	switch (cell_type)
	{
	case null_cell_type:
		array.push_back(make_shared<cell>(i, j));
		break;
	case o_cell_type:
		array.push_back(make_shared<o_cell>(i, j));
		break;
	case k_cell_type:
		shared_ptr<k_cell> k = make_shared<k_cell>(i, j, cur1, cur2);
		k_list.push_back(k);
		array.push_back(k);
		break;
	}
}
void board::connectD(ptk_cell& kcell,int x, int y){
	int k = y + 1;
	ptcell c = array[index(x, k)];
	while(k < height && typeid(*array[index(x,k)]) == typeid(o_cell))
	{
		pto_cell o = dynamic_pointer_cast<o_cell>(array[index(x,k++)]);
		o->k_down = kcell;
		kcell->d_list->push_back(o);
	}
	kcell->d_list->setminmax();
}

void board::connectR(ptk_cell& kcell, int x, int y) {
	int k = x + 1;
	while (k < width && typeid(*array[index(k, y)]) == typeid(o_cell))
	{
		pto_cell o = dynamic_pointer_cast<o_cell>(array[index(k++, y)]);
		o->k_right = kcell;
		kcell->r_list->push_back(o);
	}
	kcell->r_list->setminmax();
}

void board::connectLists() {
	for (auto& it : k_list.c_list)
	{
		if (it->down())
			connectD(it, it->x, it->y);
		if (it->right())
			connectR(it, it->x, it->y);
	}
}
void board::print(){
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			array[index(x, y)]->print(cout);
		}
		cout << "|\n";
	}
	cout << endl;
	/*for(auto& i:k_list.c_list)
	{
		cout << "k: "<<endl;
		i->printList();
	}*/
}
