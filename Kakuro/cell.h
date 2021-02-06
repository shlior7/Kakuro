#pragma once
#include "general.h"

class cell
{
public:
	int x, y;
	cell(int _x = -1,int _y = -1):x(_x),y(_y){}

	virtual ~cell(){}
	virtual void print(ostream& o){
		o << "|XX\\XX";
	}
};