#pragma once
#include "sum_cell.h"

class number_cell : public cell
{
public:
	sum_cell_ptr v_sum_cell, h_sum_cell;
	int val;
	// int options[10];
	number_cell(int x, int y) : cell(x, y), val(0)
	{
		// for (int i = 0; i < 10; i++)
		//	options[i] = i;
	}
	int get_val() const { return val; }
	operator int &()
	{
		return val;
	}

	virtual ~number_cell() {}
	virtual void print(ostream &o)
	{

		o << "|";
		if (val)
			o << setw(3) << val << "  ";
		else
			o << "     ";
	}

	friend ostream &operator<<(ostream &os, number_cell &ocell)
	{
		return os << ocell.x << "  " << ocell.y << "  " << ocell.val << endl;
	}
};
