#pragma once
#include "sum_list.h"
class o_cell;
class ok_list
{
public:
	int logical_sum, physical_sum, min, max,empty_cells;
	cell_list<o_cell> o_list;
	list<list<int>> options;
	set<int> possible;
	ok_list(int log_sum = 0) :logical_sum(log_sum), physical_sum(0),min(1),max(9), empty_cells(0){
		for (int i = 1; i <= 9; i++)
			possible.insert(i);
	}
	~ok_list(){}
	int size()const { return o_list.size(); }
	int remain() const{ return logical_sum - physical_sum; }
	void print() const{
		cout << logical_sum << endl;
		o_list.print();
	}
	void set_min_max(bool overwrite = false);
	void update_list(int n, bool add_sub, bool d_or_r);
	bool contain(set<int> poss, int n);
	void empty_list();
	void push_back(pto_cell& c);
	void add_to_sum(int n, bool d_or_r);
	void sub_from_sum(int n,bool d_or_r);
	void Calculate();
	bool Calculate_Possibility(list<int> poss,int sum, int num_cells);
	int calculate_possibilities1(list<int> poss, const list<int>::iterator cur, int carry);
	int calculate_possibilities2(list<int> poss, const list<int>::iterator cur, int carry);
};

class k_cell:public cell
{
public:
	unique_ptr<ok_list> d_list, r_list;
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