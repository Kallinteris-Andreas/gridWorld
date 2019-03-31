#include "grid.h"

grid::grid(std::string grid_name){
	std::ifstream world_file("worlds/" + grid_name + ".world", std::ios::in);
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
	grid_world = (char*) calloc(sizeof(char),(height)*
			(width/CELLS_PER_BYTE + (width%CELLS_PER_BYTE!=0)));

	//get walls
	{
		std::ifstream walls_file("worlds/" + grid_name + ".wall", std::ios::in);
		assert(walls_file.is_open());
		std::string wall_index;
		getline(walls_file, wall_index, ',');
		int No_walls = stoi(wall_index);
		getline(walls_file, wall_index, ',');
		for (int i = 0; i != No_walls; i++){
			set_cell(stoi(wall_index), wall);
			getline(walls_file, wall_index, ',');
		}
		walls_file.close();
	}

	//get grass
	{
		std::ifstream grass_file("worlds/" + grid_name + ".grass", std::ios::in);
		assert(grass_file.is_open());
		std::string grass_index = ",";
		getline(grass_file, grass_index, ',');
		while (grass_index.c_str()[0] != 10){
			set_cell(stoi(grass_index), grass);
			getline(grass_file, grass_index, ',');
		}
		grass_file.close();
	}
}
/*
//generate random grid
grid::grid(int h0, int w0){
	height = h0;
	weight = w0;
	grid_world = (char*) calloc(sizeof(char),(height)*
			(width/CELLS_PER_BYTE + (width%CELLS_PER_BYTE!=0)));
	grass_cost = 2;

	start = rand() %(height*width);
	end = rand() %(height*width);
	while (end == start)
		end = rand() %(height*width);
}

*/


void grid::set_cell(int index, int value){
	grid_world[index/CELLS_PER_BYTE] |= value << 2*(index%CELLS_PER_BYTE);
}

int grid::get_cell(int index){
	assert(index < width*height || index < 0 && "You are Out of bounds");
	return (grid_world[index/CELLS_PER_BYTE] >> 2*(index%CELLS_PER_BYTE)) & 0x3;
}

int grid::weight(int index){
	switch(get_cell(index)){
		case land: return 1;
		case grass: return grass_cost;
		case wall: assert(0/* walls dont have weights*/);
		default: assert(0 && "not valid cell type");
	}
}

int grid::weight(int index_h, int index_w){
	return weight(index_w + index_h*width);
}

void grid::print(){
	std::cout << "Height: " << height << std::endl;
	std::cout << "Width: " << width << std::endl;
	for (int i = 0; i!= height; i++){
		for (int j = 0; j!= width; j++){
			//std::cout << get_cell(i*width + j);
			std::cout << symbol((cell) get_cell(i*width + j))<<"  ";
		}
		std::cout << std::endl;
	}
}

int grid::start_x(){return start%width;}
int grid::start_y(){return start/width;}

void grid::set_grass_cost(int new_cost){grass_cost = new_cost;}

char symbol(cell c){
	switch(c){
		case land:	return 'L';
		case grass:	return 'G';
		case wall:	return 'W';
		default: assert(0 && "Not Valid Cell");
	}
}
