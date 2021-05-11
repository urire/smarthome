#include "agent_details.hpp"		// smart_home::AgentDetails

namespace smart_home {

AgentDetails::AgentDetails()
: m_id()
, m_type()
, m_config() 
, m_log("default")
, m_location()
{
}

AgentDetails::AgentDetails(const std::string& a_id, const std::string& a_type, const Location& a_location, const std::string& a_config, const std::string& a_log)
: m_id(a_id)
, m_type(a_type)
, m_config(a_config)
, m_log(a_log)
, m_location(a_location)
{
}

void AgentDetails::Id(const std::string& a_id) {
	m_id = a_id;
}

void AgentDetails::Type(const std::string& a_type) {
	m_type = a_type;
}

void AgentDetails::Room(const std::string& a_room) {
	m_location.Room(a_room);
}

void AgentDetails::Floor(const std::string& a_floor) {
	m_location.Floor(a_floor);
}

void AgentDetails::Config(const std::string& a_config) {
	m_config = a_config;
}

void AgentDetails::Log(const std::string& a_log) {
	m_log = a_log;
}

void AgentDetails::Position(const Location& a_location) {
	m_location = a_location;
}

const std::string& AgentDetails::Id() const { 
	return m_id; 
}

const std::string& AgentDetails::Type() const { 
	return m_type; 
}

const std::string& AgentDetails::Floor() const { 
	return m_location.Floor(); 
}

const std::string& AgentDetails::Room() const { 
	return  m_location.Room(); 
}

const std::string& AgentDetails::Config() const { 
	return m_config; 
}

const std::string& AgentDetails::Log() const { 
	return m_log; 
}

const Location& AgentDetails::Position() const {
	return m_location;
}

} // smart_home
