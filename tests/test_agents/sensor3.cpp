#include "sensor3.hpp"			// smart_home::Sensor3
#include "event.hpp"			// smart_home::Event
#include "shared_ptr.hpp"		// experis::SharedPtr
#include "definitions.hpp"		// SENSOR2_AND_3_TEST_SIZE
#include <cstddef>				// size_t
#include <unistd.h>				// sleep

namespace smart_home {

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new Sensor3(a_mediator, a_details));
}

Sensor3::Sensor3(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Sensor(a_mediator, a_details, true) 
{
}

void Sensor3::Run() {
	for(size_t i = 0; i < SENSOR2_AND_3_TEST_SIZE; ++i) {
		sleep(2);
		
		Publish(EventPtr(new Event(EventType("sensor3_event"), Details().Position(), "sensor3_payload")));
	}
}

} // smart_home
