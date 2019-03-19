#ifndef navigator_H_def
#define navigator_H_def
#include <iostream>
#include <string>
#include "grid.h"
//#include "grid.cc"
#include <stdlib.h>
#include <vector>
#include <cstdlib>

using namespace std;

class navigator{
	private:
		int height;
		int width;
		int startingx;//Current point X
		int startingy;//Current point Y
		int totalSum;
	    grid* map ;//= (grid)NULL;
		vector<vector<int>> discovered;
		vector<int> path;
		bool found ;
		int DFS(int x,int y);
	public:
		navigator(grid* map);
		vector<int> get_path(){return path;};//Returns the path to the destination
		int DFS();
		int BFS();//to be implemented
		int A_star();//to be implemented
		int LRTA_star();//to be implemented
		

};
#endif