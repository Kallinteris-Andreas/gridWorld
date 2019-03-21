#ifndef navigator_H_def
#define navigator_H_def
#include <iostream>
#include <string>
#include "grid.h"
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <boost/circular_buffer.hpp>

#define height map->get_height()
#define width map->get_width()

#define startingx map->get_start() % width
#define startingy map->get_start() / width
using namespace std;

class navigator{
	private:
		int totalSum;
		grid* map;
		//vector<vector<int>> discovered;
		int* discovered;
		vector<int> path;
		bool found ;

		int DFS(int x,int y);
		bool is_edge(int);
		bool is_edge(int, int);
	public:
		navigator(grid* map);
		vector<int> get_path(){return path;};//Returns the path to the destination
		int DFS();
		int BFS();
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
