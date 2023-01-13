#pragma once
#include <set>
#include <unordered_set>


#include "kcell.h"

class o_cell:public cell
{
public:
	ptk_cell k_down, k_right;
	int val, min, max;
	set<int> possibilities;
	o_cell(int x, int y) :cell(x, y),val(0),min(1),max(9){
	}
	
	operator int& () {return val;}
	virtual ~o_cell() {}
	virtual void print(ostream& o) {
		o << "|";
		if (val) o << setw(3) << val << "  ";
		else o << "     ";
	}

	friend ostream& operator<<(ostream& os,o_cell& ocell){
		return os << ocell.x<<"  "<< ocell.y<<"  "<< ocell.val<<endl;
	}
	//adds to the horizontal and vertical sums
	void fill(int n){
		if (!n)
		{
			n = val;
			val = 0;
			sub_from_sum(n);
			
		}
		else
		{
			val = n;
			add_to_sum(n);
		}
		
	}
	void add_to_sum(int n){
		if(k_down) k_down->d_list->add_to_sum(n,true);
		if (k_right) k_right->r_list->add_to_sum(n,false);
	}
	void sub_from_sum(int n) {
		if (k_down)k_down->d_list->sub_from_sum(n, true);
		if (k_right)k_right->r_list->sub_from_sum(n, false);
		//min = k_down->d_list->min > k_right->r_list->min ? k_down->d_list->min : k_right->r_list->min;
		//max = k_down->d_list->max < k_right->r_list->max ? k_down->d_list->max : k_right->r_list->max;
	}
};