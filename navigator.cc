#include "navigator.h"

using namespace std;

navigator::navigator(grid *mapp){
	map = mapp;
	totalSum = 0;
	found = false;
	path.clear();

	//Initializing the 2d adrray
	discovered.resize(height);
	for(int i= 0 ;i < height ; i++ ){
	 	discovered[i].resize(width);
	}

}

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

int navigator::BFS(){
	//init an array with no dynamic resizing
	const int capacity = 2*std::min(std::max(startingx, width-startingx),
				std::max(startingy, height - startingy));
	std::queue<int, boost::circular_buffer<int>> mq{boost::circular_buffer<int>(capacity)};
	bool *visited = new bool[height*width];
	visited[map->get_start()] = true;
	mq.push(map->get_start());

	while (!mq.empty()){
		int cur = mq.front();
		mq.pop();
		std::cout << cur << "->";
		if (map->is_end(cur))
			return 1;
		//left
		if (cur%width-1 >= 0 && visited[cur-1] == false){
			mq.push(cur-1);
			visited[cur-1] = true;
		}
		//right
		if (cur%width+1 <= width && visited[cur+1] == false){
			mq.push(cur+1);
			visited[cur+1] = true;
		}
		//up
		if (cur/width-1 >= 0 && visited[cur-height] == false){
			mq.push(cur-height);
			visited[cur-height] = true;
		}
		//down
		if (cur/width+1 <= height && visited[cur+height] == false){
			mq.push(cur+height);
			visited[cur+height] = true;
		}
	}
	return 0;
}

bool navigator::is_edge(int index){
	return is_edge(index % width, index / height);
}

bool navigator::is_edge(int x, int y){
	return (x == 0 || x == width-1 || y == 0 || y == width-1);
}
