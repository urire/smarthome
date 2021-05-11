#ifndef SABATO_AGENT_FACTORY_HPP
#define SABATO_AGENT_FACTORY_HPP

#include <exception>			// std::exception
#include <string>				// std::string
#include "mediator.hpp"			// smart_home::Mediator
#include "agent.hpp"            // smart_home::Agent
#include "shared_ptr.hpp"       // experis::SharedPtr
#include "iuncopyable.hpp"		// experis::IUncopyable

using namespace experis;

namespace smart_home {

class AgentFactory : private IUncopyable {
public:
	typedef Agent::Creator Creator;
	typedef void* CreatorHandler;
	
	struct DLErrorException : public std::exception {};
	struct FailedToOpenException : public std::exception {};

public:
	// AgentFactory() = delete;

	AgentFactory(const std::string& a_name, const std::string& a_prefix = "../../tests/so/lib", const std::string& a_postfix = ".so");
	~AgentFactory();

	SharedPtr<Agent> Create(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) const;
	const std::string& Name() const;

private:
	CreatorHandler initHandler();	
	Creator initCreator();	

private:
	std::string m_prefix;
	std::string m_postfix;
	std::string m_name;
	CreatorHandler m_handler;
	Creator m_creator; 

};

} // smart_home

#endif  // SABATO_AGENT_FACTORY_HPP