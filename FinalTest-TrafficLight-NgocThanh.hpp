#ifndef TRAFFIC_LIGHT_STATE_MACHINE_HPP
#define TRAFFIC_LIGHT_STATE_MACHINE_HPP

#include <iostream>
using namespace std;

class ILightState {
public:
    // LightState(LightColor init_state);
    // LightColor getState const;
    // void wait() const;
    virtual void changeLightState() =0;
    virtual void reportLightState() =0;
};

class TrafficLight {
private:
    ILightState* m_state;
public:
    TrafficLight();
    void setState(ILightState* state);
//    ILightState* getState();
    void changeLight();
    void reportLight();
};

class YellowLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    YellowLight(TrafficLight* context);
    void changeLightState();
    void reportLightState();
};

class GreenLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    GreenLight(TrafficLight* context);
    void changeLightState();
    void reportLightState(); 
};

class RedLight : public ILightState {
private:
    TrafficLight* m_context;
public:
    RedLight(TrafficLight* context);
    void changeLightState();
    void reportLightState();
};

#endif //TRAFFIC_LIGHT_STATE_MACHINE_HPP
