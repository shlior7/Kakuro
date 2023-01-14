#pragma once
#include "number_cell.h"

template <class T>
class matrix
{
public:
	vector<T> array;
	size_t width, height;
	matrix(size_t _width, size_t _height) : width(_width), height(_height)
	{
	}
	size_t index(int x, int y) const { return x + width * y; }
};

class board : public matrix<cell_ptr>
{
public:
	cell_list<sum_cell> sum_cells;
	board(size_t _width, size_t _height) : matrix(_width, _height) {}
	board(std::vector<std::vector<int>> board) : matrix(board[0].size() / 2, board.size()) { get_board(board); }
	void get_board(istream &in);
	void get_board(std::vector<std::vector<int>> board);
	//	void get_board(istream& in, ostream& out);
	void push_current(int cur1, int cur2, int i, int j);
	void connectVerticals(sum_cell_ptr &sum_cell, int x, int y);
	void connectHorizontals(sum_cell_ptr &sum_cell, int x, int y);
	void connectLists();
	void save(ofstream &out);
	void solve();
	vector<vector<int>> toVector();
	void print();
};
