
#include "navigator.h"


using namespace std;
//Constructor
navigator::navigator(grid* map){
	map = map;
	totalSum = 0;
	found = false;
	
	//Initializing the 2d adrray
	discovered.resize(height);
	for(int i= 0 ;i < height ; i++ ){
	 	discovered[i].resize(width);
	}

}
int navigator::DFS(){
	//INITIALIZE to be added soon
	
	totalSum += DFS(startingx,startingy);
	return totalSum;
}

int navigator::DFS(int x,int y){
	discovered[y][x]= 1;
	int index = y*width+x;
	
	cout << y <<" "<<x<<" "<<index<<" "<<map->is_wall(index)<<"\n";
	if( map->is_end(index)){
		found = true;
		cout << "yeahhhhhhhhhhhhhhhhh";
		return 0;
	}
	//going up
	if(y-1 >= 0 && !found){
		if((!map->is_wall((y-1)*width+x )&& discovered[y-1][x]==0)){
			totalSum += DFS(x,y-1);
		}
	}
	//going down
	if(y+1 <height && !found){
		if((!map->is_wall((y+1)*width+x )&& discovered[y+1][x]==0)){
			totalSum += DFS(x,y+1);
		}
	}
	//going left
	if(x-1 >= 0 && !found){
		if((!map->is_wall(y*width+x-1 )&& discovered[y][x-1]==0)){
			totalSum += DFS(x-1,y);
		}
	}
	//going right
	if(x+1 <height && !found){
		if((!map->is_wall(y*width+x+1 )&& discovered[y][x+1]==0)){
			totalSum += DFS(x+1,y);
		}
	}
	//return 1;
	std::cout << index << std::endl;
	return map->weight(index);

}

bool navigator::is_edge(int index){
	return is_edge(index % width, index / height);
}

bool navigator::is_edge(int x, int y){
	return (x == 0 || x == width-1 || y == 0 || y == width-1);
}
