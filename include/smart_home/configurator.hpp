#ifndef SABATO_CONFIGURATOR_HPP
#define SABATO_CONFIGURATOR_HPP

#include <exception>			// std::exception
#include <string>				// std::string
#include "agent.hpp"			// smart_home::Agent
#include "shared_ptr.hpp"		// experis::SharedPtr

using namespace experis;

namespace smart_home {

class Configurator {
public:
	struct InvalidArgumentException : public std::exception {};
	struct MissingArgumentException : public std::exception {};
	struct AgentAlreadyInitializedException : public std::exception {};	

	template<typename Container, typename Stream>
	static void Configurate(Container& a_container, Stream& a_stream);

private:
	template<typename Container, typename Stream>
	static void addAgentDetails(Container& a_container, Stream& a_ss);
	static void removeWhitespaces(std::string& a_str);
	static bool startsWith(const std::string& a_str, const std::string& a_prefix);
	static bool endsWith(const std::string& a_str, const std::string& a_postfix);
	static bool parseFieldAndValue(const std::string& a_line, std::string& a_field, std::string& a_value);
	static void getAgentDetails(const std::string& a_field, const std::string& a_value, AgentDetails& a_details);

};

} // smart_home

#include "inl/configurator.inl"

#endif	// SABATO_CONFIGURATOR_HPP
