#include "event.hpp"		// smart_home::Event

namespace smart_home {

Event::Event(const EventType& a_type, const Location& a_location, const std::string& a_payload)
: m_time()
, m_type(a_type)
, m_location(a_location)   
, m_payload(a_payload) 
{
}

const Timestamp& Event::Time() const {
	return m_time;
}

const EventType& Event::Type() const {
	return m_type;
}

const Location& Event::Position() const {
	return m_location;
}

const std::string& Event::Payload() const {
	return m_payload;
}

} // smart_home
