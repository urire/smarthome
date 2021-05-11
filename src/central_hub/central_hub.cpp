#include "central_hub.hpp"		// smart_home::CentralHub
#include "configurator.hpp"		// smart_home::Configurator
#include "reader.hpp"			// smart_home::Reader
#include <sstream>				// std::stringstream
#include <fstream>				// std::ifstream

using namespace experis;

namespace smart_home {

size_t CentralHub::s_maxEvents = 1000000;

CentralHub::CentralHub(const std::string& a_config)
: IUncopyable()
, m_loggers()
, m_factories()
, m_agents()
, m_events(s_maxEvents)
, m_extractor(m_events)
, m_publisher(new Publisher(m_events))
, m_subscriber(new Subscriber(m_extractor))
, m_mediator(new Mediator(m_publisher, m_subscriber))
{
	initHub(a_config);
}

CentralHub::~CentralHub() {
	Shutdown();
}

void CentralHub::Start() {
	for(size_t i = 0; i < m_agents.size(); ++i) {
		m_agents[i]->Start();
	}

	m_extractor.Start();
}

void CentralHub::Shutdown() {
	m_extractor.Shutdown();	

	for(size_t i = 0; i < m_agents.size(); ++i) {
		m_agents[i]->Shutdown();
	}
}

void CentralHub::LoggerMessage(const std::string& a_logger, std::string& a_msg) {
	a_msg = m_loggers.Get(a_logger).Message();
}

void CentralHub::initHub(const std::string& a_config) {
	std::stringstream stream;
	Reader::Read(a_config, stream);

	DetailsContainer details;
	Configurator::Configurate(details, stream);

	for(DetailsContainer::const_iterator itr = details.begin(); itr != details.end(); ++itr) {
		initAgent(*itr);
	}
}

void CentralHub::initAgent(const AgentDetails& a_details) {
	const std::string& log = a_details.Log();
	const std::string& type = a_details.Type();

	if(!m_loggers.Contains(log)) {
		m_loggers.Add(LoggerPtr(new Logger(log)));
	}

	if(!m_factories.Contains(type)) {
		m_factories.Add(FactoryPtr(new AgentFactory(type)));
	}
	
	m_mediator->SetLogger(LoggerPtr(&m_loggers.Get(log)));
	m_agents.push_back(m_factories.Get(type).Create(m_mediator, a_details));	
}

} // smart_home
