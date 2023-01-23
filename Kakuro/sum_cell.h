#pragma once
#include "block.h"

class sum_cell : public cell
{
public:
	unique_ptr<block> vertical_block, horizontal_block;
	// cell_list<o_cell> d_list, r_list;
	sum_cell(int x, int y, int _vertical, int _horizontal) : cell(x, y)
	{
		if (_vertical > 0)
			vertical_block = make_unique<block>(_vertical);
		if (_horizontal > 0)
			horizontal_block = make_unique<block>(_horizontal);
	}
	bool validate()
	{
		if (vertical_block && vertical_block->logical_sum != vertical_block->physical_sum)
			return false;
		if (horizontal_block && horizontal_block->logical_sum != horizontal_block->physical_sum)
			return false;

		return true;
	}
	virtual ~sum_cell() {}
	virtual void print(ostream &o)
	{
		o << "|" << setw(2) << (!vertical_block ? "  " : to_string(v_logical_sum())) << "\\" << setw(2) << (!horizontal_block ? "  " : to_string(h_logical_sum()));
	}
	int v_logical_sum() { return vertical_block ? vertical_block->logical_sum : 0; }
	int h_logical_sum() { return horizontal_block ? horizontal_block->logical_sum : 0; }
	int v_physical_sum() { return vertical_block ? vertical_block->physical_sum : 0; }
	int h_physical_sum() { return horizontal_block ? horizontal_block->physical_sum : 0; }
	void printList() const
	{
		vertical_block->print();
		horizontal_block->print();
	}
};

#define sum_cell_ptr shared_ptr<sum_cell>
