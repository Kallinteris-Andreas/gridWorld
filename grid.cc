#ifndef grid_def
#define grid_def
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <chrono>
#include <thread>
#include <assert.h>
#include <unistd.h>
#include "grid.h"
#define CELLS_PER_BYTE 4

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
		int weight(int);
		int weight(int, int);
		int get_height() {return height;};
		int get_width() {return width;};
		int get_start() {return start;};
		int is_end(int index) {return (index == end);};
};

grid::grid(std::string grid_name){
	std::ifstream world_file(grid_name + ".world", std::ios::in);
	assert(world_file.is_open());
	std::string line;

	//get the dimensions
	{
		getline(world_file, line);
		height = stoi(line.substr(11, line.find("x")-11));
		width = stoi(line.substr(line.find("x")+1));
	}

	//get indexes
	{
		getline(world_file, line);
		start = stoi(line.substr(10));
		getline(world_file, line);
		end = stoi(line.substr(13));
		getline(world_file, line);
		grass_cost = stoi(line.substr(11));
	}

	world_file.close();
	//malloc world
	grid_world = (char*) calloc(1, (height/CELLS_PER_BYTE + (height%CELLS_PER_BYTE!=0))*
			(width/CELLS_PER_BYTE + (width%CELLS_PER_BYTE!=0)));

	//get walls
	{
		std::ifstream walls_file(grid_name + ".wall", std::ios::in);
		assert(walls_file.is_open());
		std::string wall_index = ",";
		while (wall_index.c_str()[0] == 10){
			getline(walls_file, wall_index, ',');
			set_cell(stoi(wall_index), wall);
		}
		walls_file.close();
	}

	//get grass
	{
		std::ifstream grass_file(grid_name + ".grass", std::ios::in);
		assert(grass_file.is_open());
		std::string grass_index = ",";
		while (grass_index.c_str()[0] == 10){
			getline(grass_file, grass_index, ',');
			set_cell(stoi(grass_index), grass);
		}
		grass_file.close();
	}

}

void grid::set_cell(int index, int value){
	grid_world[index/CELLS_PER_BYTE] |= value << 2*(index%CELLS_PER_BYTE);
}

int grid::get_cell(int index){
	return (grid_world[index/CELLS_PER_BYTE] >> 2*(index%CELLS_PER_BYTE)) & 0x3;
}

int grid::weight(int index){
	switch(get_cell(index)){
		case land: return 1;
		case grass: return grass_cost;
		case Wall: assert(0/* walls dont have weights*/);
	}
	assert(0);
}

int grid::weight(int index_h, int index_w){
	return weight(index_w + index_h*width);
}

#endif
