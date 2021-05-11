#include "event_type.hpp"

namespace smart_home {

const std::string EventType::s_all = "*";

const std::string& EventType::All() {
	return s_all;
}

EventType::EventType(const std::string& a_name, const std::string& a_room, const std::string& a_floor)
: m_name(a_name)
, m_location(a_room, a_floor)
{
}

void EventType::Name(const std::string& a_name) {
	m_name = a_name;
}

void EventType::Room(const std::string & a_room) {
	m_location.Room(a_room);
}

void EventType::Floor(const std::string & a_floor) {
	m_location.Floor(a_floor);
}

void EventType::Position(const Location & a_location) {
	m_location = a_location;
}

const std::string& EventType::Name() const {
	return m_name;
}

const std::string& EventType::Room() const {
	return m_location.Room();
}

const std::string& EventType::Floor() const {
	return m_location.Floor();
}

const Location & EventType::Position() const {
	return m_location;
}

bool EventType::ContainsAll() const {
	return m_name == s_all || m_location.Room() == s_all || m_location.Floor() == s_all;
}

bool EventType::operator<(const EventType& a_other) const {
	return m_name < a_other.m_name || (m_name == a_other.m_name && m_location < a_other.m_location);
}

} // smart_home
