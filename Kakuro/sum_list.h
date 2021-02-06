#pragma once
#include "cell.h"
template <class T>
class cell_list
{
public:
	list<shared_ptr<T>> c_list;
	int sum;
	cell_list():sum(0){}
	operator list<shared_ptr<T>>&(){
		return c_list;
	}
	int size()const { return c_list.size(); }
	void push_back(shared_ptr<T>& ptr){
		c_list.push_back(ptr);
	}

	void print()const{
		for(auto& i:c_list)
		{
			cout << *i << endl;
		}
	}
};
