#include "location.hpp"     // samrt_home::Location

namespace smart_home {

Location::Location(const std::string& a_floor, const std::string& a_room) 
: m_floor(a_floor)
, m_room(a_room) 
{
}

void Location::Floor(const std::string& a_floor) {
    m_floor = a_floor;
}

void Location::Room(const std::string& a_room) {
    m_room = a_room;
}

const std::string& Location::Floor() const {
    return m_floor;
}

const std::string& Location::Room() const {
    return m_room;
}

bool Location::operator<(const Location& a_other) const {
	return m_floor < a_other.m_floor || (m_floor == a_other.m_floor && m_room < a_other.m_room);
}

} // smart_home
