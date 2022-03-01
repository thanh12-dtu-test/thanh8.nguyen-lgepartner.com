#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include "FinalTest-TrafficLight-NgocThanh.hpp"
#include "FinalTest-TrafficLight-NgocThanh.cpp"
using namespace std;

enum LightState {
    RedLight,
    YellowLight,
    GreenLight,
};
LightState currentState = RedLight;

std::map<std::string, unsigned int> time_config;

bool force_red = false,
	force_green = false,
	resume = false,
	stop = false,
	restart = false;
	
std::mutex mutex_lock;
std::condition_variable force_condition, restart_condition;

int getConfigFromFile() {
    std::ifstream inputFile;
    inputFile.open("FinalTest-TimeConfig-NgocThanh.cfg"); //std::ios::in
    if(inputFile.is_open()) {
        std::string line, word;
        while(std::getline(inputFile, line)) {
            std::vector<std::string> words;
            std::istringstream iss(line);
            while(iss >> word) {
                words.push_back(word);
            }
            time_config.insert(std::make_pair(words[0], std::stoi(words[1])));
        }
//        inputFile.close();
        return EXIT_SUCCESS;
    }
    else {
        std::cerr << "Could not open the file" << std::endl;
        return EXIT_FAILURE;
    }
}

void processLightEvent(TrafficLight &traffic_light, unsigned int time_delay) {
	traffic_light.reportLight();
    cout<< "...wait for " <<time_delay<< " second" <<endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_delay));
    traffic_light.changeLight();
//    std::unique_lock<std::mutex> lock(mutex_lock);
    if(force_red || force_green) {
//    	condition_lock.wait(lock,[] { 
//				return force_red; 
//			});
		force_condition.notify_one();
    }
//    	else if(force_green) {
//    		currentState = GreenLight;
//			}
//	if(stop) {
//		stop_condition.notify_one();
//	}
//if(restart){
//	cout<"bbb";
//	restart_condition.notify_one();
//	
//}
				
}

void processForceRed() {
//	std::thread([] {
    	while(true) {
        	std::unique_lock<mutex> lock(mutex_lock);
        	force_condition.wait(lock, [] { 
				return force_red || force_green; 
			});
        	TrafficLight traffic_light;
        	if(force_green) {
        		traffic_light.changeLight();
			}
        	traffic_light.reportLight();
    		cout<< "...forced" <<endl;
//    		std::this_thread::sleep_for(std::chrono::seconds(3));
        	//force_red = false;
//        	stop_condition.wait(lock, [] { 
//				return stop; 
//			});
      	}
//    }).detach();
}

void lauchTrafficLight() {
//	std::unique_lock<mutex> lock(mutex_lock);
//    restart_condition.wait(lock, [] { 
//		return restart==true || stop==false; 
//	});
//	cout<<"aaa";
    TrafficLight traffic_light;
    // traffic_light.setState(currentState);
    while(true) {
//    	if(restart) {
//    		traffic_light = new TrafficLight();
//    		restart = false;
//		}
    	if(stop == false) {
    		if(getConfigFromFile() == EXIT_SUCCESS) {
    		unsigned int time_delay;
    		switch(currentState) {
    			case RedLight : {
    				time_delay = time_config.find("SECOND_FROM_RED_TO_GREEN")->second;
    				processLightEvent(traffic_light, time_delay);
        			currentState = GreenLight;
        			
					
					break;
				}
                case GreenLight : {
    				time_delay = time_config.find("SECOND_FROM_GREEN_TO_YELLOW")->second;
    				processLightEvent(traffic_light, time_delay);
        			currentState = YellowLight;
        			
					break;
				}
                case YellowLight : {
    				time_delay = time_config.find("SECOND_FROM_YELLOW_TO_RED")->second;
    				processLightEvent(traffic_light, time_delay);
        			currentState = RedLight;
        			
					break;
				}
			}
			time_config.clear();
		}
		}
    		
    }
//    cout<< "Traffic light has turned off" <<endl;
}

void setUserCommand() {
	string command;
	std::map<string, int> user_command {{"force-red", 1}, {"force-green", 2}, {"resume", 3}, {"stop", 4}, {"restart", 5}};
	while(true) {
		std::getline(std::cin, command);
		switch(user_command.find(command)->second) {
			case 1 : {
				force_red = true;
				force_green = false;
//				{
//					std::unique_lock<mutex> lock(mutex_lock);
//					force_red = true;
//					TrafficLight traffic_light;
//        			traffic_light.reportLight();
//    				cout<< "...forced" <<endl;
//        			force_red = false;
//				}
//				processForceRed();
//				condition_lock.notify_one();
				break;
			}
			case 2 : {
				force_green = true;
				force_red = false;
				break;
			}
			
			case 3 : {
				force_green = false;
				force_red = false;
				stop = false;
				break;
			}
			
			case 4 : {
				stop = true;
				cout<< "All lights has turned off" <<endl;
				break;
			}
			
			case 5 : {
				restart = true;
				stop = false;
				cout<< "Traffic lights has restarted" <<endl;
				break;
			}
			
			default : break;
			
		}
	}
}

int main() {
    std::thread traffic_light_thread(&lauchTrafficLight);
    std::thread user_command_thread(&setUserCommand);
    std::thread force_red_thread(&processForceRed);
    traffic_light_thread.join();
    user_command_thread.join();
    force_red_thread.join();
//    for (const auto& n : time_config) {
//		std::cout << n.first << " = " << n.second << "; ";
//	}
    return 0;
}
