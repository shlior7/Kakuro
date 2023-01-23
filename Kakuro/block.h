#pragma once
#include "cell_list.h"

class number_cell;
class block
{
public:
	int logical_sum, physical_sum, min, max;
	cell_list<number_cell> numbers_block;
	block(int log_sum = 0) : logical_sum(log_sum), physical_sum(0), min(1), max(9) {}
	~block() {}
	int size() const { return numbers_block.size(); }
	int remain() const { return logical_sum - physical_sum; }
	void print() const
	{
		// cout << logical_sum << endl;
		numbers_block.print();
	}
	void setminmax()
	{
		int len = size();
		max = (2 * logical_sum - len * (len - 1)) / 2;
		min = (2 * logical_sum + len * len - 21 * len + 20) / 2;
		// cout << min << "  " << max << endl;
	}
	void push_back(number_cell_ptr &c) { numbers_block.push_back(c); }
	void add_to_sum(int n)
	{
		physical_sum += n;
	}
};
