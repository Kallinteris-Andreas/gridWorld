#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "grid.h"
#include "navigator.cc"
using namespace std;

double get_time(void) {
    struct timeval ttime;
    gettimeofday(&ttime , NULL);
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

int main(int argc, char** argv){
	grid map("easy");
	
	navigator nav(&map);
	cout << nav.DFS();

	return 1;
}
