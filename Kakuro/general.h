#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <iomanip>


#define ptcell shared_ptr<cell>
#define ptk_cell shared_ptr<k_cell>
#define pto_cell shared_ptr<o_cell>

using namespace std;

