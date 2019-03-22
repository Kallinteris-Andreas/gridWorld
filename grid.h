#ifndef grid_H_def
#define grid_H_def
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <chrono>
#include <thread>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

#define CELLS_PER_BYTE 4

enum cell{
	land = 0x0,
	grass = 0x3,
	wall = 0x1,
};

class grid {
	private:
		int height;
		int width;
		int start;
		int end;
		int grass_cost;
		char* grid_world;
	private:
		void set_cell(int, int);
		int get_cell(int);
	public:
		grid(std::string);
		grid(int,int);
		void print();
		void set_grass_cost(int);
		int weight(int);
		int start_x();
		int start_y();
		int weight(int, int);
		int get_height() {return height;};
		int get_width() {return width;};
		int get_start() {return start;};
		int get_end(){return end;};
		int is_end(int index) {return (index == end);};
		int is_wall(int index) {return (get_cell(index) == wall);};
};

char symbol(cell);

#endif
