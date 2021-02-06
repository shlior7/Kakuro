#pragma once
#include "Ocell.h"

template<class T>
class matrix
{
public:
	vector<T> array;
	size_t width, height;
	matrix(size_t _width, size_t _height):width(_width),height(_height){
		
	}
	size_t index(int x, int y) const { return x + width * y; }
};

class board: public matrix<ptcell>
{
public:
	cell_list<k_cell> k_list;
	board(size_t _width, size_t _height):matrix(_width, _height) {}
	void get_board(istream& in);
//	void get_board(istream& in, ostream& out);
	void push_current(int cur1, int cur2, int i, int j);
	void connectD(ptk_cell& kcell, int x, int y);
	void connectR(ptk_cell& kcell, int x, int y);
	void connectLists();
	void save(ofstream& out);
	void solve();
	void print();
};
