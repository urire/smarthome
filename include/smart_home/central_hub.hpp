#ifndef SABATO_CENTRAL_HUB_HPP
#define SABATO_CENTRAL_HUB_HPP

#include <string>					// std::string
#include <vector>					// std::vector
#include <map>						// std::map
#include <cstddef>					// size_t
#include "agent.hpp"				// smart_home::Agent
#include "event.hpp"				// smart_home::Event
#include "mediator.hpp"				// smart_home::Mediator
#include "extractor.hpp"			// smart_home::Extractor
#include "agent_factory.hpp"		// smart_home::AgentFactory
#include "shared_ptr.hpp"			// experis::SharedPtr
#include "lookup_table.hpp"			// experis::LookupTable
#include "iuncopyable.hpp"			// experis::IUncopyable
#include "thread_safe_queue.hpp"	// experis::ThreadSafeQueue

using namespace experis;

namespace smart_home {

class CentralHub : private IUncopyable {
public:
	typedef SharedPtr<Agent> AgentPtr; 
	typedef SharedPtr<Event> EventPtr; 
	typedef SharedPtr<Logger> LoggerPtr; 
	typedef SharedPtr<IPublisher> PublisherPtr; 
	typedef SharedPtr<ISubscriber> SubscriberPtr; 
	typedef SharedPtr<Mediator> MediatorPtr; 
	typedef SharedPtr<AgentFactory> FactoryPtr;
	typedef std::vector<AgentPtr> AgentContainer;
	typedef std::vector<AgentDetails> DetailsContainer;
	typedef LookupTable<std::string, Logger> LoggerLUT; 
	typedef LookupTable<std::string, AgentFactory> AgentLUT;
	typedef ThreadSafeQueue<EventPtr> EventQueue;	

public:
	// CentralHub() = delete;

	CentralHub(const std::string& a_config);
	~CentralHub();
	
	void Start();
	void Shutdown();
	void LoggerMessage(const std::string& a_logger, std::string& a_msg);
	
private:
	void initHub(const std::string& a_config);
	void initAgent(const AgentDetails& a_details);

private:
	static size_t s_maxEvents;
		
private:	
	LoggerLUT m_loggers;				
	AgentLUT m_factories;
	AgentContainer m_agents;
	EventQueue m_events;		
	Extractor m_extractor;		
	PublisherPtr m_publisher;
	SubscriberPtr m_subscriber;
	MediatorPtr m_mediator;
	
};

} // smart_home

#endif	// SABATO_CENTRAL_HUB_HPP
