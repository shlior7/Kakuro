#pragma once
#include "kcell.h"

class o_cell:public cell
{
public:
	ptk_cell k_down, k_right;
	int val;
	//int options[10];
	o_cell(int x, int y) :cell(x, y),val(0){
		//for (int i = 0; i < 10; i++)
		//	options[i] = i;
	}

	operator int& () {
		return val;
	}

	virtual ~o_cell() {}
	virtual void print(ostream& o) {
		
		o << "|";
		if (val) o << setw(3) << val << "  ";
		else o << "     ";
	}

	friend ostream& operator<<(ostream& os,o_cell& ocell){
		return os << ocell.x<<"  "<< ocell.y<<"  "<< ocell.val<<endl;
	}
};