#include "sensor1.hpp"			// smart_home::TempSensor
#include "event.hpp"			// smart_home::Event
#include <sstream>				// std::stringstream
#include <cstddef>				// size_t, NULL
#include <unistd.h>				// sleep
#include <stdlib.h>     		// srand, rand 
#include <time.h>       		// time 

using namespace experis;

namespace smart_home {

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new TempSensor(a_mediator, a_details));
}

TempSensor::TempSensor(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Sensor(a_mediator, a_details, true) 
, m_lower(-5)
, m_upper(55)
, m_period(12)
, m_units("C")
{
	srand(time(NULL));	
}

void TempSensor::Run() {
	for(size_t i = 0; i < 1; ++i) {
		sleep(m_period);
		
		int number = rand() % (m_upper - m_lower + 1) + m_lower;
		
		std::stringstream ss;
		
		ss << number;
		
		Publish(EventPtr(new Event(EventType("TEMPERATURE_EVENT", Details().Room(), Details().Floor()), Details().Position(), ss.str())));
	}
}

} // smart_home

