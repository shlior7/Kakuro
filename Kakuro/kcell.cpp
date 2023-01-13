#include "Ocell.h"

void ok_list::set_min_max(bool overwrite) {
	int len = empty_cells;
	int sum = remain();
	int sum_max = 0, sum_min = 0;
	auto it_max = possible.begin();
	auto it_min = possible.rbegin();
	if(!possible.empty())
	for (int i = 1;i <= len-1;++i,++it_max,++it_min)
	{
		sum_max += *it_max;
		sum_min += *it_min;
	}
	max = sum - sum_max;
	min = sum - sum_min;
	//max = (2 * sum - len * (len - 1)) / 2;
	//min = (2 * sum + len * len - 21 * len + 20) / 2;
	if (min < 1) min = 1;
	if (max > 9) max = 9;
	//empty_cells = len;
}
void ok_list::update_list(int n, bool add_or_sub, bool d_or_r) {

	for (auto& o : o_list.c_list)
	{
		if (!o->val) {
			if (o->possibilities.empty())
				throw 1;
			int i = 1;
			while (i != 10)
			{
				const bool contain_i = d_or_r ? contain(o->k_down->d_list->possible, i): contain(o->k_right->r_list->possible, i) ;
				if (d_or_r || contain_i)
				{
					if (i<min || i>max)	o->possibilities.erase(i);
					else o->possibilities.insert(i);
				}
				i++;
			}
				if (empty_cells == 2 && !(remain() % 2))
					o->possibilities.erase(remain() / 2);
				if (add_or_sub)
					o->possibilities.erase(n);//delete all possibilities from the list
				else if (contain(o->k_down->d_list->possible, n) && contain(o->k_right->r_list->possible, n)) {
					o->possibilities.insert(n);//add the possibility backtracking
				}
				/*
				int i = max + 1;
				while (i != min)
				{
					o->possibilities.erase(i);
					i++; if (i > 9) i = 1;
				}
				*/
				possible.insert(o->possibilities.begin(), o->possibilities.end());
				cout << "";
		}
	}
}
bool ok_list::contain(set<int> poss,int n){
	if (poss.find(n) == poss.end())
		return false;
	return true;
}
void ok_list::empty_list(){
	for (auto& o : o_list.c_list)
	{
		if (o->val) {
			o->add_to_sum(-(o->val));
			o->val = 0;
		}
	}	
}

void ok_list::push_back(pto_cell& c) {
	o_list.push_back(c);
	empty_cells++;
}

void ok_list::add_to_sum(int n,bool d_or_r){
	physical_sum += n;
	empty_cells--;
	possible.erase(n);
	set_min_max();
	update_list(n, true, d_or_r);
}

void ok_list::sub_from_sum(int n,bool d_or_r) {
	physical_sum -= n;
	empty_cells++;
	possible.insert(n);
	set_min_max();
	update_list(n, false, d_or_r);
}
void ok_list::Calculate(){
	list<int> poss;
	Calculate_Possibility(poss, logical_sum, empty_cells);
}
bool ok_list::Calculate_Possibility(list<int> poss,int sum,int num_cells){
	if(!num_cells)
	{
		if(!sum)
		{
			options.push_back(poss);
			return true;
		}
		return false;
	}
	for(int i=1;i<=9;i++)
	{
		if (std::find(poss.begin(),poss.end(),i) == poss.end()) {
			poss.push_back(i);
			if (Calculate_Possibility(poss, sum - i, num_cells - 1))
				return true;
			poss.pop_back();
		}
	}
}
int ok_list::calculate_possibilities1(list<int> poss,const list<int>::iterator cur, int carry) {
	int carr = 0;
	for(auto i= cur;i!=poss.end();++i)
	{
		auto next = i;
		if (carry) {
			if (i != poss.begin())
				--next;
			if (*i - 1 > 0 && *i - 1 != *(next)) {
				(*i)--;
				calculate_possibilities1(poss,i, 0);
			}
		}
		else{
			next = i;
			if (*i != *poss.rbegin())
				++next;
			if (*i + 1 < 9  && *i + 1 != *(next)) {
				(*i)++;
				calculate_possibilities1(poss,i, 1);
			}
		}
		if (!carry)
			options.push_back(poss);
	}
	return carr;
}
int ok_list::calculate_possibilities2(list<int> poss, const list<int>::iterator cur, int carry) {
	int carr = 0;
	for (auto i = cur; i != poss.end(); ++i)
	{
		auto next = i;
		//if (carry) {
		if (i != poss.begin())
			--next;
		if (*i - 1 > 0 && *i - 1 != *(next)) {
			(*i)--;
			carr = calculate_possibilities2(poss, i, 0) - 1;
		}
		//}
		//else{
		next = i;
		if (*i != *poss.rbegin())
			++next;
		if (*i + 1 < 9 && *i + 1 != *(next)) {
			(*i)++;
			carr = calculate_possibilities2(poss, i, 1) + 1;
		}
		//}
	}
	return carr;
}