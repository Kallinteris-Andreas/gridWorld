
#include "navigator.h"


using namespace std;
//Constructor

navigator::navigator(grid *mapp){
	map = mapp;
	//height = mapp->get_height();
	//width = map->get_width();
	//startingx = map->get_start() % width;
//	startingy = map->get_start() / width;
	totalSum = 0;
	found = false;
	path.clear();

	//Initializing the 2d adrray
	discovered.resize(height);
	for(int i= 0 ;i < height ; i++ ){
	 	discovered[i].resize(width);
	}

}//Initial DFS function
int navigator::DFS(){
	path.clear();
	totalSum = 0;
	found = false;
	discovered.resize(height);
	for(int i= 0 ;i < height ; i++ ){
		discovered[i].clear();
	 	discovered[i].resize(width);
	}

	totalSum += DFS(startingx,startingy);
	return totalSum;
}
int navigator::DFS(int x,int y){

	discovered[y][x]= 1;
	int index = y*width+x;
	path.push_back(index);
	
	//cout << y <<" "<<x<<" "<<index<<" "<< map->is_wall(index)<<"\n";

	if( map->is_end(index)){//When we reach Destination 
		found = true;
		cout << "Reached Destination"<<endl;
		return 0;
	}
	int pick = 1;
	int flag[4] = {0,0,0,0};
	srand (time(NULL));
	
	for(int i =1; i<5;i++){
		//Visiting all four directions(up,down,..) randomly
		while(found == false){
			pick = rand()%4 +1;
			if (flag[pick]!=1){
				flag[pick] = 1;
				break;
			}

		}
		switch(pick){
			case 1:
				//going up
				if(y-1 >= 0 && !found){//IF found is TRUE there is no need to further expand,so terminate
					if((!map->is_wall((y-1)*width+x )&& discovered[y-1][x]==0)){
						totalSum += DFS(x,y-1);
					}
				}
				break;
			case 2:
				//going down
				if(y+1 <height && !found){
					if((!map->is_wall((y+1)*width+x )&& discovered[y+1][x]==0)){
						totalSum += DFS(x,y+1);
					}	
				}
				break;
			case 3:
				//going left
				if(x-1 >= 0 && !found){
					if((!map->is_wall(y*width+x-1 )&& discovered[y][x-1]==0)){
						totalSum += DFS(x-1,y);
					}
				}
				break;
			case 4:
				//going right
				if(x+1 <width && !found){
					if((!map->is_wall(y*width+x+1 )&& discovered[y][x+1]==0)){
						totalSum += DFS(x+1,y);
					}
				}
				break;
			default:
				assert(0 && "not supposed to reach this");
				break;
		}
	}
	//returning the cost of the current cell
	return map->weight(index);

}

bool navigator::is_edge(int index){
	return is_edge(index % width, index / height);
}

bool navigator::is_edge(int x, int y){
	return (x == 0 || x == width-1 || y == 0 || y == width-1);
}
