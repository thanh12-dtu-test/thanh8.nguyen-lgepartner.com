#include "FinalTest-TrafficLight-NgocThanh.hpp"

TrafficLight::TrafficLight() {
    m_state = new RedLight(this);
}

void TrafficLight::setState(ILightState* state) {
	m_state = state;
}

//ILightState* TrafficLight::getState() {
//	return m_state;
//}

void TrafficLight::reportLight() {      
	m_state->reportLightState();
}

void TrafficLight::changeLight(){
    m_state->changeLightState();
}

YellowLight::YellowLight(TrafficLight* context) : m_context(context) {}

void YellowLight::changeLightState() {
    m_context->setState(new RedLight(m_context));
}
    
void YellowLight::reportLightState() {
    cout<< "YELLOW light";
}

GreenLight::GreenLight(TrafficLight* context): m_context(context) {}

void GreenLight::changeLightState() {
    m_context->setState(new YellowLight(m_context));
}
    
void GreenLight::reportLightState() {
    cout<< "GREEN light";
} 

RedLight::RedLight(TrafficLight* context) : m_context(context) {}

void RedLight::changeLightState() {
    m_context->setState(new GreenLight(m_context));
}

void RedLight::reportLightState() {
    cout<< "RED light";
}
