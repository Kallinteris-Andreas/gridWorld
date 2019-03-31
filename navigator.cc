#include "navigator.h"

using namespace std;


navigator::navigator(grid *mapp){
	map = mapp;
	totalSum = 0;
	found = false;
	path.clear();

	discovered =(int*)calloc(height*width,sizeof(int));
}

int navigator::DFS(){
	path.clear();
	totalSum = 0;
	found = false;
	if(discovered!= NULL){
	 	free(discovered);	
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
	totalSum = 0;
	int counter = 0;
	//init an array with no dynamic resizing
	int capacity = 2*std::min(std::max(startingx, width-startingx),
				std::max(startingy, height - startingy));
	std::queue<int, boost::circular_buffer<int>> mq{boost::circular_buffer<int>(capacity)};
	bool *visited = new bool[height*width];
	visited[map->get_start()] = true;
	mq.push(map->get_start());

	while (!mq.empty()){
		int cur = mq.front();
		mq.pop();
		std::cout << cur << "->";
		counter ++;
		if (map->is_end(cur)){
			cout<<endl<<"Path's length is: "<<counter<<endl;
			//free(visited);
			return counter;
		}
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

void navigator::push_back(vector<cell_key*> &v,int index,int cost){
	float dist = distance(index);
	cell_key* c = new cell_key();
	c->index = index;
	c->weight = (dist + cost);

	v.push_back(c);
}
float navigator::distance(int index){ 
	int xx = map->get_end()%width - index%width;
	int yy = map->get_end()/width - index/width;

	return 1*(abs(xx)+abs(yy)) ;//Manhattan Distance
	//return sqrt(xx*xx+yy*yy);
}
int navigator::exists(vector<cell_key*> &v,int index_){
	for(int i = 0;i<v.size();i++){
		if(v.at(i)->index == index_){
			return i;
		}
	}
	return -1;
}
int navigator::LRTA_star_cost(int s,int s_,int* H){
	if(H[s_] == 0){
		return distance(s);
	}else{
		return H[s_] + map->weight(s_); //!!!!!!!!
	}
}
int navigator::LRTA_star(){
	free(discovered);
	discovered =(int*)calloc(height*width,sizeof(int));
	int* H =(int*)calloc(height*width,sizeof(int));
	//Initializing member variables
	int** result=(int**)malloc(height*width*sizeof(int*));
	for(int i=0;i<height*width;i++){
		result[i] = (int*)malloc(4*sizeof(int));
	}

	for(int i =0;i<width*height;i++){
		for(int j=0;j<4;j++){
			result[i][j] = -1;
		}
		
	}

	path.clear();
	totalSum =0;

	int x = startingx;
	int y = startingy;
	int index = y*width + x;

	direction action,prevAction ;
	
	int prev_index = -1;
	int min_index=-1;
	int min_weight = max_int;
	int dir = 0;
	int w = 0;

	while(!map->is_end(index)){
		totalSum +=map->weight(index);
		//cout <<"--> "<< y <<" "<<x<<" "<<index<<"\n";
		
		if(H[index] == 0){
			H[index] = distance(index);
		}
		if(prev_index > -1){
			result[prev_index][prevAction] = index;
			
			min_weight = max_int;
			y = prev_index/width;
			x = prev_index%width;

			if(y-1 >= 0 ){
				dir = (y-1)*width+x ;
				if(!map->is_wall(dir) && result[prev_index][2]!=-1){
					if(LRTA_star_cost(prev_index,dir,H) < min_weight ){
						min_weight = LRTA_star_cost(prev_index,dir,H);
						min_index = dir;
					}
				}	
			}
			if(y+1 <height){
				dir = (y+1)*width+x ;
				if(!map->is_wall(dir) && result[prev_index][3]!=-1){
					if(LRTA_star_cost(prev_index,dir,H) < min_weight){
						min_weight = LRTA_star_cost(prev_index,dir,H);
						min_index = dir;
					}
				}	
			}
			if(x-1 >= 0 ){
				dir = y*width+x-1;
				if(!map->is_wall(dir)&& result[prev_index][0]!=-1){
					if(LRTA_star_cost(prev_index,dir,H) < min_weight){
						min_weight = LRTA_star_cost(prev_index,dir,H);
						min_index = dir;
					}
				}
			}
			if(x+1 <width){
				dir = y*width+x+1;
				if(!map->is_wall(dir)&& result[prev_index][1]!=-1){
					if(LRTA_star_cost(prev_index,dir,H) < min_weight){
						min_weight = LRTA_star_cost(prev_index,dir,H);
						min_index = dir;
					}
				}
			}
			H[prev_index] = min_weight;
		}
		y = index/width;
		x = index%width;
		min_weight =max_int;
		min_index = -1;
		//Minimize the cost of the next move
		if(y-1 >= 0 ){
			dir = (y-1)*width+x ;
			if(!map->is_wall(dir)){
				w = LRTA_star_cost(index,dir,H);
				if(w==min_weight){//if you find more than one good path,
								 //pick the closest to the finsih
					if(distance(dir)<=distance(min_index)){
						min_index = dir;
					}
				}else if(w < min_weight){
					min_weight = w ;
					min_index = dir;
					action = direction::up;
				}//cout<<LRTA_star_cost(index,dir,H)<<" ,y:"<<dir/width<<" ,x:"<<dir%width<<endl;
			}	
		}
		if(y+1 <height){
			dir = (y+1)*width+x ;
			if(!map->is_wall(dir)){
				w = LRTA_star_cost(index,dir,H);
				if(w==min_weight){
					if(distance(dir)<=distance(min_index)){
						min_index = dir;
					}
				}else if(w < min_weight){
					min_weight = w ;
					min_index = dir;
					action = direction::down;
				}
			}	
		}
		if(x-1 >= 0 ){
			dir = y*width+x-1;
			if(!map->is_wall(dir)){
				w = LRTA_star_cost(index,dir,H);
				if(w==min_weight){
					if(distance(dir)<=distance(min_index)){
						min_index = dir;
					}
				}else if(w < min_weight){
					min_weight = w ;
					min_index = dir;
					action = direction::left;
				}
			}
		}
		if(x+1 <width){
			dir = y*width+x+1;
			if(!map->is_wall(dir)){
				w = LRTA_star_cost(index,dir,H);
				if(w==min_weight){
					if(distance(dir)<=distance(min_index)){
						min_index = dir;
					}
				}else if(w < min_weight){
					min_weight = w ;
					min_index = dir;
					action = direction::right;
				}
			}
		}

		prevAction = action;
		prev_index = index;
		index = min_index;
		y = index/width;
		x = index%width;		

		path.insert(path.begin(),(min_index));

	
	}
	/*
	//Debbuging code for  table
	cout<<endl;
	for(int i=0;i<width*height;i++){
		cout<<i<<". ";
		for(int y=0;y<4;y++){
			if (result[i][y]==-1){
				std::printf("  -");
			}else{
				std::printf("%3d",result[i][y]);
			}

		}
		cout<<endl;
	}*/
	cout<<endl;
	for(int i=0;i<height;i++){
		for(int y=0;y<width;y++){
				if(H[i*width+y] == max_int){
					std::printf("   -");
				}else{
					std::printf("%4d",H[i*width+y]);
				}
		}
		cout<<endl;
	}
	
	free(H);
	for(int i=0;i<height*width;i++){
		free(result[i]);
	}
	//free(result);

	return totalSum;
}

int navigator::A_star(){
	//Initializer 
	free(discovered);
	discovered =(int*)calloc(height*width,sizeof(int));
	path.clear();

	int x = startingx;
	int y = startingy;
	int index = y*width + x;
	
	vector<cell_key*> v ;
	
	int min_index = 0;
	float min_weight = max_int;
	int prev_index = -1;
	int min_v=0;
	int cost = 0;
	int dir = 0;int ind = 0;

	while(!map->is_end(index)){
		//cout << y <<" "<<x<<" "<<index<<"\n";

		if(y-1 >= 0 ){
			dir = (y-1)*width+x ;
			if(!map->is_wall(dir) && dir != map->get_start()){

				cost = discovered[index] + map->weight(dir);
				if(discovered[dir]==0){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}else if(cost < discovered[dir]){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}
		
			}	
		}
		if(y+1 <height){
			dir = (y+1)*width+x ;
			if((!map->is_wall(dir)&& dir != map->get_start())){
				cost = discovered[index] + map->weight(dir);
				if(discovered[dir]==0){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}else if(cost < discovered[dir]){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}
			}	
		}
		if(x-1 >= 0 ){
			dir = y*width+x-1;
			if((!map->is_wall(dir )&& dir != map->get_start())){
				cost = discovered[index] + map->weight(dir);
				if(discovered[dir]==0){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}else if(cost < discovered[dir]){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}
			}
		}
		if(x+1 <width){
			dir = y*width+x+1;
			if((!map->is_wall(dir)&& dir != map->get_start())){
				cost = discovered[index] + map->weight(dir);
				if(discovered[dir]==0){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}else if(cost < discovered[dir]){
					discovered[dir] = cost;
					push_back(v,dir,cost);
				}
			}
		}
		min_weight = max_int;
		for(int i = 0; i<v.size(); i++){
			//cout<<"Index: "<<v.at(i)->index/width<<" : "<<v.at(i)->index%width<<" , weight: "<<v.at(i)->weight<<":discovered: "<<discovered[v.at(i)->index]<<endl;
			if((v.at(i))->weight < min_weight){
				min_index = v.at(i)->index;
				min_weight = v.at(i)->weight;
				min_v = i;
			}
		}
		prev_index = index;
		index = v.at(min_v)->index;
		y = index/width;
		x =index%width;

		free(v.at(min_v));
		v.erase(v.begin() + min_v);
	}
	discovered[map->get_start()] = -1;
//Debbuging code for discovered table
	for(int i=0;i<height;i++){
		for(int y=0;y<width;y++){
			//cout<<discovered[i*width+y]<<" ";
			std::printf("%4d",discovered[i*width+y]);
		}
		cout<<endl;
	}

	//BELOW CODE PRINTS THE OPTIMAL PATH,USING BACKTRACKING of discovered table
	
	index = map->get_end();
	min_weight = max_int;
	min_index = map->get_end();

	while(index!=map->get_start()){
		min_weight = max_int;

		if(y-1 >= 0 ){
			dir = (y-1)*width+x ;
			if(!map->is_wall(dir) && discovered[dir] != 0){
				if(discovered[dir]<min_weight){
					min_weight = discovered[dir];
					min_index = dir;
				}
			}	
		}
		if(y+1 <height){
			dir = (y+1)*width+x ;
			if((!map->is_wall(dir) && discovered[dir] != 0)){
				if(discovered[dir]<min_weight){
					min_weight = discovered[dir];
					min_index = dir;
				}
			}	
		}
		if(x-1 >= 0 ){
			dir = y*width+x-1;
			if((!map->is_wall(dir) && discovered[dir] != 0)){
				if(discovered[dir]<min_weight){
					min_weight = discovered[dir];
					min_index = dir;
				}
			}
		}
		if(x+1 <width){
			dir = y*width+x+1;
			if((!map->is_wall(dir) && discovered[dir] != 0)){
				if(discovered[dir]<min_weight){
					min_weight = discovered[dir];
					min_index = dir;
				}
			}
		}
		path.insert(path.begin(),(min_index));
		index = min_index;
		y = index/width;
		x = index%width;
	}
	return discovered[map->get_end()];
}


bool navigator::is_edge(int index){
	return is_edge(index % width, index / height);
}

bool navigator::is_edge(int x, int y){
	return (x == 0 || x == width-1 || y == 0 || y == width-1);
}
