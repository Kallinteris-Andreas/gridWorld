#include "navigator.h"

using namespace std;


navigator::navigator(grid *mapp){
	map = mapp;
	totalSum = 0;
	found = false;
	path.clear();

	//Initializing the 2d adrray
	discovered =(int*)calloc(height*width,sizeof(int));
}

void navigator::push_back(vector<cell_key*> &v,int index){
	float dist = distance(index);
	cell_key* c = new cell_key();
	c->index = index;
	c->weight = dist + map->weight(index);

	v.push_back(c);
}
float navigator::distance(int index){ //THIS is the heuristic function,we may change it
	int xx = map->get_end()%width - index%width;
	int yy = map->get_end()/width - index/width;
	cout<<"weight : "<< sqrt(xx*xx+yy*yy) <<endl;
	return sqrt(xx*xx+yy*yy);
}
int navigator::A_star(){
	//Initializer ,TO be added
	
	path.clear();
	int x = startingx;
	int y = startingy;
	int index = y*width + x;
	
	vector<cell_key*> v ;
	
	int min_index = 0;
	int min_weight = max_int;
	int min_v=0;

	while(!map->is_end(index)){
		std::cout<<index<<endl;

		discovered[index] = 1;
		totalSum += map->weight(index);

		min_weight = max_int;
		path.push_back(index);
			
			if(y-1 >= 0 ){
					if((!map->is_wall((y-1)*width+x )&& discovered[(y-1)*width+x]==0)){
						push_back(v,(y-1)*width+x);
				}	
			}
			if(y+1 <height){
					if((!map->is_wall((y+1)*width+x )&& discovered[(y+1)*width+x]==0)){
						push_back(v,(y+1)*width+x);
					}	
			}
			if(x-1 >= 0 ){
					if((!map->is_wall(y*width+x-1 )&& discovered[y*width+x-1]==0)){
						push_back(v,y*width+x-1 );
					}
			}
			if(x+1 <width){
					if((!map->is_wall(y*width+x+1 )&& discovered[y*width+x+1]==0)){
						push_back(v,y*width+x+1 );
					}
			}
		
		cout<<v.size()<<endl;
		for(int i = 0; i<v.size(); i++){
			if((v.at(i))->weight < min_weight){
				min_index = v.at(i)->index;
				min_weight = v.at(i)->weight;
				min_v = i;
			}
		}
		index = v.at(min_v)->index;
		y = index/width;
		x =index%width;

		delete v.at(min_v);
		v.erase(v.begin() + min_v);
	}
	return totalSum;
}
int navigator::DFS(){
	path.clear();
	totalSum = 0;
	found = false;
	if(discovered!= NULL){
	 	delete discovered;	
	}
	discovered = (int*)calloc(height*width,sizeof(int));

	totalSum += DFS(startingx,startingy);
	return totalSum;
}

int navigator::DFS(int x,int y){
	
	int index = y*width+x;
	discovered[index]= 1;
	path.push_back(index);
	
	//cout << y <<" "<<x<<" "<<index<<" "<< map->is_wall(index)<<"\n";

	if( map->is_end(index)){//When we reach Destination 
		found = true;
		cout << "Reached Destination"<<endl;
		return 0;
	}
	int pick = 1;
	
	for(int i =1; i<5;i++){

		pick = i;
		switch(pick){
			case 1:
				//going up
				if(y-1 >= 0 && !found){//IF found is TRUE,there is no need to further expand,so terminate
					if((!map->is_wall((y-1)*width+x )&& discovered[(y-1)*width+x]==0)){
						totalSum += DFS(x,y-1);
					}
				}
				break;
			case 2:
				//going down
				if(y+1 <height && !found){
					if((!map->is_wall((y+1)*width+x )&& discovered[(y+1)*width+x]==0)){
						totalSum += DFS(x,y+1);
					}	
				}
				break;
			case 3:
				//going left
				if(x-1 >= 0 && !found){
					if((!map->is_wall(y*width+x-1 )&& discovered[y*width+x-1]==0)){
						totalSum += DFS(x-1,y);
					}
				}
				break;
			case 4:
				//going right
				if(x+1 <width && !found){
					if((!map->is_wall(y*width+x+1 )&& discovered[y*width+x+1]==0)){
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
