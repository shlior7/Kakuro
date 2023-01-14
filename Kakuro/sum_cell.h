#pragma once
#include "cell_list.h"
class number_cell;
class block
{
public:
	int logical_sum, physical_sum, min, max;
	cell_list<number_cell> numbersBlock;
	block(int log_sum = 0) : logical_sum(log_sum), physical_sum(0), min(1), max(9) {}
	~block() {}
	int size() const { return numbersBlock.size(); }
	int remain() const { return logical_sum - physical_sum; }
	void print() const
	{
		cout << logical_sum << endl;
		numbersBlock.print();
	}
	void setminmax()
	{
		int len = size();
		max = (2 * logical_sum - len * (len - 1)) / 2;
		min = (2 * logical_sum + len * len - 21 * len + 20) / 2;
		cout << min << "  " << max << endl;
	}
	void push_back(number_cell_ptr &c) { numbersBlock.push_back(c); }
	void add_to_sum(int n) { physical_sum += n; }
};

class sum_cell : public cell
{
public:
	unique_ptr<block> vertical_block, horizontal_block;
	// cell_list<o_cell> d_list, r_list;
	sum_cell(int x, int y, int _vertical, int _horizontal) : cell(x, y)
	{
		if (_vertical)
			vertical_block = make_unique<block>(_vertical);
		if (_horizontal)
			horizontal_block = make_unique<block>(_horizontal);
	}

	virtual ~sum_cell() {}
	virtual void print(ostream &o)
	{
		o << "|" << setw(2) << (!vertical_block ? "  " : to_string(down())) << "\\" << setw(2) << (!horizontal_block ? "  " : to_string(right()));
	}
	int down() { return vertical_block ? vertical_block->logical_sum : 0; }
	int right() { return horizontal_block ? horizontal_block->logical_sum : 0; }
	int down_sum() { return vertical_block ? vertical_block->physical_sum : 0; }
	int right_sum() { return horizontal_block ? horizontal_block->physical_sum : 0; }

	void printList() const
	{
		vertical_block->print();
		horizontal_block->print();
	}
};

#define sum_cell_ptr shared_ptr<sum_cell>
