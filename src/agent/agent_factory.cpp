#include "agent_factory.hpp"    // smart_home::AgentFactory
#include <dlfcn.h>		        // dlopen, dlerror, dlsym, dlclose, RTLD_LAZY

using namespace experis;

namespace smart_home {

AgentFactory::AgentFactory(const std::string& a_name, const std::string& a_prefix, const std::string& a_postfix)
: IUncopyable()
, m_prefix(a_prefix)
, m_postfix(a_postfix)
, m_name(a_name)
, m_handler(initHandler())
, m_creator(initCreator()) 
{
}

AgentFactory::~AgentFactory() {
	if(m_handler) {
		dlclose(m_handler);
	}
}

SharedPtr<Agent> AgentFactory::Create(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) const {
	return m_creator(a_mediator, a_details);
}

const std::string& AgentFactory::Name() const {
	return m_name;
}

AgentFactory::CreatorHandler AgentFactory::initHandler() {
	std::string lib = m_prefix + m_name + m_postfix;

	CreatorHandler handle = dlopen(lib.c_str(), RTLD_LAZY);
	if(!handle) {		
		throw FailedToOpenException();
	}
	
	return handle;
}

AgentFactory::Creator AgentFactory::initCreator() {
	dlerror();			
    Creator creator = reinterpret_cast<Creator>(dlsym(m_handler, Agent::CreatorString().c_str()));
    if (dlerror()) {
		throw DLErrorException();
	}
	
	return creator;
}

} // smart_home
