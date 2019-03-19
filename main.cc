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

	map->print();

	navigator* nav = new navigator(map);
	//solving with DFS 
	cout << nav->DFS()<<endl;
	//printing path
	vector<int> v = nav->get_path();
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	cout << " -> "<< *i ;
    }
    cout <<endl;
   	

	return 1;
}
