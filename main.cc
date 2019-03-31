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
		cout<<"11.To toggle grass cost(2 / 5)"<<endl;
		cout<<"--Current grass cost is : "<<map->get_grass_cost()<<endl;
		cout<<"--Press anything else to exit--"<< endl;
		cout<<"--------------------------------\n"<<endl;
		
		cin>>pick;
		
		switch(pick){
			case 1:
				free(map);
				map = new grid("default");
				//delete nav;
				nav = new navigator(map);
				break;
			case 2:
				free(map);
				map = new grid("easy");
				free(nav);
				nav = new navigator(map);
				break;
			case 3:
				free(map);
				map = new grid("hard_a");
				free(nav);
				nav = new navigator(map);
				break;
			case 4:
				free(map);
				map = new grid("hard_b");
				free(nav);
				nav = new navigator(map);
				break;
			case 5:
				free(map);
				map = new grid("hard_c");
				free(nav);
				nav = new navigator(map);
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
				if (nav->BFS())
					std::cout << "found with BFS search" << std::endl;
				else
					std::cout << "not found with BFS search" << std::endl;
				break;
			case 8:
				cout <<"A* cost is : "<< nav->A_star()<<endl;
				v = nav->get_path();
				std::cout << "Optimal path steps: " << v.size() << std::endl;
			    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
			    	cout << " -> y: "<< (*i)/map->get_width() <<" x: "<< (*i)%map->get_width()<<endl;
			    }
				break;
			case 9:
				cout <<"LRTA* cost is : "<< nav->LRTA_star()<<endl;
				v = nav->get_path();
				std::cout << "Path steps: " << v.size() << std::endl;
			    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
			    	cout << " -> y: "<< (*i)/map->get_width() <<" x: "<< (*i)%map->get_width()<<endl;
			    }
				break;
			case 10:
				map->print();
				break;
			case 11:
				if(map->get_grass_cost() == 2){
					map->set_grass_cost(5);
				}else{
					map->set_grass_cost(2);
				}
				break;
			default:
				cout<<"Terminating..."<<endl;
				return 0;
		}
	}
	

	return 1;
}
