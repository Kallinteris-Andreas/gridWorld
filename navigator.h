#ifndef navigator_H_def
#define navigator_H_def
#include <iostream>
#include <string>
#include "grid.h"
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <math.h>
#include <boost/circular_buffer.hpp>
#include <boost/heap/priority_queue.hpp>

#define height map->get_height()
#define width map->get_width()

#define startingx map->get_start() % width
#define startingy map->get_start() / width
#define max_int 214748364

using namespace std;
struct cell_key{
	int index;
	float weight;
};
enum direction{
	left,
	right,
	up,
	down,
	none,
};
class navigator{
	private:
		int totalSum;
		grid* map;
		int* discovered;
		vector<int> path;
		
		bool found ;

		int DFS(int x,int y);

		bool is_edge(int);
		bool is_edge(int, int);
		//Push cell with index to the given vector
		void push_back(vector<cell_key*> &v,int index,int cost);
		//Checks if index exists in vector<cell_key> v
		bool exists(vector<cell_key*> &v,int index);
		// Returns the distance from the end to the index
		float distance(int index); 
		int LRTA_star_cost(int s,int s_,int* H);
	public:
		navigator(grid* map);
		vector<int> get_path(){return path;};//Returns the path to the destination
		int DFS();
		int BFS();
		int A_star();
		int LRTA_star();
};





#endif
