#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "grid.cc"

double get_time(void) {
    struct timeval ttime;
    gettimeofday(&ttime , NULL);
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

int main(int argc, char** argv){
	grid map("easy.world");
}
