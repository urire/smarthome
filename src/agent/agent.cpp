#include "agent.hpp"		// smart_home::Agent

namespace smart_home {

std::string Agent::CreatorString() {
	return "CreateAgent";
}

Agent::Agent(const MediatorPtr& a_mediator, const AgentDetails& a_details)
: IUncopyable()
, m_logger(a_mediator->GetLogger())
, m_details(a_details) 
{
}

Agent::~Agent() {
}

const AgentDetails& Agent::Details() const { 
	return m_details; 
}

void Agent::Log(const std::string& a_msgToLog) {
	m_logger->Log(a_msgToLog);
}

} // smart_home
