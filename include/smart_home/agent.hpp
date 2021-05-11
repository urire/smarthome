#ifndef SABATO_AGENT_HPP
#define SABATO_AGENT_HPP

#include <string>				// std::string
#include "irunner.hpp"          // smart_home::IRunner
#include "agent_details.hpp"	// smart_home::AgentDetails
#include "event.hpp"			// smart_home::Event
#include "mediator.hpp"			// smart_home::Mediator
#include "logger.hpp"      		// smart_home::Logger
#include "iuncopyable.hpp"		// experis::IUncopyable
#include "shared_ptr.hpp"		// experis::SharedPtr

using namespace experis;

namespace smart_home {

class Agent : private IUncopyable, public IRunner {
public:
	typedef SharedPtr<Logger> LoggerPtr;
	typedef SharedPtr<Event> EventPtr;
	typedef SharedPtr<Agent> AgentPtr;
	typedef SharedPtr<Mediator> MediatorPtr;
	typedef AgentPtr (*Creator)(const MediatorPtr& a_mediator, const AgentDetails& a_details);

public:
	static std::string CreatorString();	

public:
	// Agent() = delete;
	// Agent(const Agent&) = default;
	// Agent& operator=(const Agent&) = default;

	Agent(const MediatorPtr& a_mediator, const AgentDetails& a_details);
	virtual ~Agent();	
		
	const AgentDetails& Details() const;	
	void Log(const std::string& a_msgToLog);

	virtual void Start() {}
    virtual void Shutdown() {}  
	virtual void Run() {}

private:	
	LoggerPtr m_logger;
	AgentDetails m_details;

};

extern "C" {

experis::SharedPtr<smart_home::Agent> CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);

}

} // smart_home

#endif	// SABATO_AGENT_HPP
