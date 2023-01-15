#pragma once
#include "cell.h"

template <class T>
class cell_list
{
public:
	list<shared_ptr<T>> the_list;
	int sum;
	cell_list() : sum(0) {}
	operator list<shared_ptr<T>> &()
	{
		return the_list;
	}
	int size() const { return the_list.size(); }
	void push_back(shared_ptr<T> &ptr)
	{
		the_list.push_back(ptr);
	}
	void print() const
	{
		for (auto &i : the_list)
		{
			cout << *i << endl;
		}
	}
};
