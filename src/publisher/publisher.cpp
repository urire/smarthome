#include "publisher.hpp"		// smart_home::Publisher

namespace smart_home {

Publisher::Publisher(EventQueue& a_events)
: m_events(a_events) 
{
}

void Publisher::Publish(const EventPtr& a_event) {
	m_events.Enqueue(a_event);
}
	
} // smart_home
