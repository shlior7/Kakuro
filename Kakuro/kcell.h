#pragma once


#include "sum_list.h"
class o_cell;
class ok_list
{
public:
	int logical_sum, physical_sum, min, max ;
	cell_list<o_cell> o_list;
	ok_list(int log_sum = 0) :logical_sum(log_sum), physical_sum(0),min(1),max(9) {}
	~ok_list(){}
	int size()const { return o_list.size(); }
	int remain() const{ return logical_sum - physical_sum; }
	void print() const{
		cout << logical_sum << endl;
		o_list.print();
	}
	void setminmax() {
		int len = size();
		max = (2 * logical_sum - len * (len - 1)) / 2;
		min = (2 * logical_sum + len * len - 21 * len + 20) / 2;
		cout << min << "  " << max << endl;
	}
	void push_back(pto_cell& c){o_list.push_back(c);}
	void add_to_sum(int n) { physical_sum += n; }
	
};

class k_cell:public cell
{
public:
	unique_ptr<ok_list> d_list, r_list;
	//cell_list<o_cell> d_list, r_list;
	k_cell(int x, int y, int _down, int _right) :cell(x, y){
		if (_down) d_list = make_unique<ok_list>(_down);
		if (_right) r_list = make_unique<ok_list>(_right);
	}

	virtual ~k_cell() {}
	virtual void print(ostream& o) {
		o <<"|" << setw(2) << (!d_list ?"  ":to_string(down())) <<"\\"<<
			setw(2) << (!r_list ? "  " : to_string(right()));
	}
	int down() { return d_list ? d_list->logical_sum : 0; }
	int right() { return r_list ? r_list->logical_sum : 0; }
	int down_sum() { return d_list ? d_list->physical_sum : 0; }
	int right_sum() { return r_list ? r_list->physical_sum : 0; }
	
	void printList() const{
		d_list->print();
		r_list->print();
		
	}
};