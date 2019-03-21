#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "grid.h"
#include "navigator.h"
using namespace std;

double get_time(void) {
    struct timeval ttime;
    gettimeofday(&ttime , NULL);
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

int main(int argc, char** argv){
	// Testing functions \/
	grid* map = new grid("easy");
	cout<<rand()%4 +1<<endl;

	navigator* nav = new navigator(map);
	nav->BFS();
	/*
	//solving with DFS 
	cout << nav->DFS()<<endl;
	//printing path
	vector<int> v = nav->get_path();
	std::cout << "path steps: " << v.size() << std::endl;
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	cout << " -> "<< *i ;
    }
    int path_cost = 0;
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	path_cost += map->weight(*i);
    }
    cout <<endl;
    std::cout << "path_cost= " << path_cost << std::endl;
    cout <<endl;
	*/
	

	return 1;
}
