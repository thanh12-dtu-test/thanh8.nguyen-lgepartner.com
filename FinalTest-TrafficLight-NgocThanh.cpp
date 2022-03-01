#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// class TrafficLight {
// public:
//     void changeState()
// }

class ILightState {
public:
    // LightState(LightColor init_state);
    // LightColor getState const;
    // void wait() const;
    // void nextState();
    virtual void changeLightState() =0;
};

class TrafficLight {
    private:
    ILightState* m_state;
public:
    // TrafficLight(){
    //     m_state = new RedLight(this)
    // }
    TrafficLight();
    void setState(ILightState* state);
    void handle();
};



#include "FinalTest-TrafficLight-NgocThanh.hpp"

void TrafficLight::setState(ILightState* state) {
		m_state = state;
	}
void TrafficLight::handle(){
        m_state->changeLightState();
    }


class YellowLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    RedLight(TrafficLight* context) : m_context(context) {}
    void changeLightState() {
        m_context->setState(new RedLight(m_context));
    }
    void display() {
        cout<< "Yellow light" <<endl;
    }
};

class GreenLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    GreenLight(TrafficLight* context): m_context(context) {}
    void changeLightState() {
        m_context->setState(new YellowLight(m_context));
    }
    void display() {
        cout<< "Green light" <<endl;
    }
    
};

class RedLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    RedLight(TrafficLight* context) : m_context(context) {}
    void changeLightState() {
        m_context->setState(new GreenLight(m_context));
    }
    void display() {
        cout<< "Red light" <<endl;
    }
};

map<string, int> time_config;

void getConfigFromFile() {
    std::ifstream inputFile;
    inputFile.open("FinalTest-TimeConfig-NgocThanh.cfg", std::ios::in);
    if(inputFile.is_open()) {
        std::string line, word;
        while(std::getline(inputFile, line)) {
            std::vector<std::string> words;
            std::istringstream iss(line);
            while(iss >> word) {
                words.push_back(word);
            }
            time_config.push_back(words[0], std::stoi(words[1]));
        }
        inputFile.close();
        return EXIT_SUCCESS;
    }
    else {
        std::cerr << "Could not open the file" << std::endl;
        return EXIT_FAILURE;
    }
}


void lauchTrafficLight() {
    enum ILightState {
        RedLight,
        YellowLight,
        GreenLight,
    } *currentState = RedLight;
    TrafficLight light;
    light.m_state = currentState;
    while(true) {
        light.display();
        light.changeLightState();
    }

}
int main() {

    lauchTrafficLight();

    return 0;
}

#endif
