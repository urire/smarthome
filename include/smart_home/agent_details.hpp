#ifndef SABATO_AGENT_DETAILS_HPP
#define SABATO_AGENT_DETAILS_HPP

#include <string>			// std::string
#include "location.hpp"     // smart_home::Location

namespace smart_home {

class AgentDetails {
public:
	// AgentDetails(const AgentDetails&) = default;
	// AgentDetails& operator=(const AgentDetails&) = default;
	// ~AgentDetails() = default;

	AgentDetails();
	AgentDetails(const std::string& a_id, const std::string& a_type, const Location& a_location, const std::string& a_config, const std::string& a_log);

	void Id(const std::string& a_id);
	void Type(const std::string& a_type);
	void Floor(const std::string& a_floor);
	void Room(const std::string& a_room);
	void Config(const std::string& a_config);
	void Log(const std::string& a_log);
	void Position(const Location& a_location);

	const std::string& Id() const;
	const std::string& Type() const;
	const std::string& Floor() const;
	const std::string& Room() const;	
	const std::string& Config() const;
	const std::string& Log() const;
	const Location& Position() const;	

private:
	std::string m_id;
	std::string m_type;	
	std::string m_config;
	std::string m_log;
	Location m_location;	

};

} // smart_home

#endif	// SABATO_AGENT_DETAILS_HPP
