#include "sensor2.hpp"			// smart_home::Sensor2
#include "event.hpp"			// smart_home::Event
#include "shared_ptr.hpp"		// experis::SharedPtr
#include "definitions.hpp"		// SENSOR2_AND_3_TEST_SIZE
#include <cstddef>				// size_t
#include <unistd.h>				// sleep

namespace smart_home {

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new Sensor2(a_mediator, a_details));
}

Sensor2::Sensor2(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Sensor(a_mediator, a_details, true) 
{
}

void Sensor2::Run() {
	for(size_t i = 0; i < SENSOR2_AND_3_TEST_SIZE; ++i) {
		sleep(1);
		
		Publish(EventPtr(new Event(EventType("sensor2_event"), Details().Position(), "sensor2_payload")));
	}
}

} // smart_home
