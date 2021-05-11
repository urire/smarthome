#include "sensor4.hpp"			// smart_home::Sensor4
#include "event.hpp"			// smart_home::Event
#include "shared_ptr.hpp"		// experis::SharedPtr
#include "definitions.hpp"		// SENSOR2_AND_3_TEST_SIZE, CONTROLLER1_EVENT_TYPE
#include <cstddef>				// size_t
#include <unistd.h>				// sleep

namespace smart_home {

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new Sensor4(a_mediator, a_details));
}

Sensor4::Sensor4(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Sensor(a_mediator, a_details, true) 
{
}

void Sensor4::Run() {	
	Publish(EventPtr(new Event(EventType(CONTROLLER1_EVENT_TYPE, "2", "2"), Details().Position(), "sensor2_payload")));
    Publish(EventPtr(new Event(EventType(CONTROLLER1_EVENT_TYPE, "2", "2"), Details().Position(), "sensor2_payload")));	
}

} // smart_home
