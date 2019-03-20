#ifndef navigator_H_def
#define navigator_H_def
#include <iostream>
#include <string>
#include "grid.h"
#include <stdlib.h>
#include <vector>

#define height map->get_height()
#define width map->get_width()

#define startingx map->get_start() % width
#define startingy map->get_start() / width
using namespace std;

class navigator{
	private:
		int totalSum;
		grid* map;//= (grid)NULL;
		vector<vector<int>> discovered;
		bool found;
		int DFS(int x,int y);
		bool is_edge(int);
		bool is_edge(int, int);
	public:
		navigator(grid* map);
		int DFS();
		int BFS();//to be implemented
		int A_star();//to be implemented
		int LRTA_star();//to be implemented
};

enum direction{
	left,
	right,
	above,
	below,
};

#endif
