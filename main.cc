#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "grid.h"
#include "navigator.h"
using namespace std;

double get_time(void) {
    struct timeval ttime;
    gettimeofday(&ttime , NULL);
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}
vector<int> v ;
grid* map = new grid("easy");
navigator* nav = new navigator(map);
int pick;

int main(int argc, char** argv){

	while(true){
		 


		cout<<"\n------------------------"<<endl;
		cout<<"1.Load default world"<<endl;
		cout<<"2.Load easy world"<<endl;
		cout<<"3.Load hard_a world"<<endl;
		cout<<"4.Load hard_b world"<<endl;
		cout<<"5.Load hard_c world"<<endl;
		cout<<"6.Solve with DFS"<<endl;
		cout<<"7.Solve with BFS"<<endl;
		cout<<"8.Solve with A*"<<endl;
		cout<<"9.Solve with LRTA*"<<endl;
		cout<<"10.Print current map"<<endl;
		cout<<"--Press anything else to exit--"<< endl;
		cout<<"--------------------------------\n"<<endl;
		
		cin>>pick;

		switch(pick){
			case 1:
				delete map;
				map = new grid("default");
				break;
			case 2:
				delete map;
				map = new grid("easy");
				break;
			case 3:
				delete map;
				map = new grid("hard_a");
				break;
			case 4:
				delete map;
				map = new grid("hard_b");
				break;
			case 5:
				delete map;
				map = new grid("hard_c");
				break;
			case 6:
				cout << nav->DFS()<<endl;
				v = nav->get_path();
				std::cout << "path steps: " << v.size() << std::endl;
			    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
			    	cout << " -> y: "<< (*i)/map->get_width() <<" x: "<< (*i)%map->get_width()<<endl;
			    }
				break;
			case 7:
				cout << nav->BFS()<<endl;
				break;
			case 8:
				cout <<"A* cost is : "<< nav->A_star()<<endl;
				v = nav->get_path();
				std::cout << "path steps: " << v.size() << std::endl;
			    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
			    	cout << " -> y: "<< (*i)/map->get_width() <<" x: "<< (*i)%map->get_width()<<endl;
			    }
				break;
			case 9:
			cout<<"Not implemented yet"<<endl;
				break;
			case 10:
				map->print();
				break;
			default:
				cout<<"Terminating..."<<endl;
				return 0;
		}
	}
	

	// Testing functions \/
	grid* map = new grid("easy");
	
	navigator* nav = new navigator(map);
	cout <<"A* cost is : "<< nav->A_star()<<endl;
	//cout << nav->BFS()<<endl;
	//cout << nav->DFS()<<endl;
	vector<int> v = nav->get_path();
	std::cout << "path steps: " << v.size() << std::endl;
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	cout << " -> "<< *i ;
    }

	/*
	//solving with DFS 
	cout << nav->DFS()<<endl;
	//printing path
	vector<int> v = nav->get_path();
	std::cout << "path steps: " << v.size() << std::endl;
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	cout << " -> "<< *i ;
    }
    int path_cost = 0;
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
    	path_cost += map->weight(*i);
    }
    cout <<endl;
    std::cout << "path_cost= " << path_cost << std::endl;
    cout <<endl;
	*/
	

	return 1;
}
