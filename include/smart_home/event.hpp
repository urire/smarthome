#ifndef SABATO_EVENT_HPP
#define SABATO_EVENT_HPP

#include <string>				// std::string
#include "event_type.hpp"		// smart_home::EventType
#include "timestamp.hpp"		// smart_home::Timestamp
#include "location.hpp"     	// samrt_home::Location
#include "shared_ptr.hpp"		// experis::SharedPtr

using namespace experis;

namespace smart_home {

class Event {
public:
	// Event() = delete;
	// Event(const Event&) = default;
	// Event& operator=(const Event&) = default;
	// ~Event() = default;
	
	Event(const EventType& a_type, const Location& a_location = Location(), const std::string& a_payload = "");
	
	const Timestamp& Time() const;
	const EventType& Type() const;
	const Location& Position() const;
	const std::string& Payload() const;

private:
	Timestamp m_time;
	EventType m_type;
	Location m_location;
	std::string m_payload;
	
};

} // smart_home

#endif	// SABATO_EVENT_HPP
