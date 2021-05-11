#include "controller.hpp"		// smart_home::Controller

namespace smart_home {

Controller::Controller(const MediatorPtr& a_mediator, const AgentDetails& a_details) 
: Agent(a_mediator, a_details)
, m_subscriber(a_mediator->GetSubscriber())
, m_subscribers()
{  
}

Controller::~Controller() {   
}

void Controller::Subscribe(const EventType& a_eventType, const HandlerPtr& a_handler) {
    m_subscribers.push_back(a_handler);
    m_subscriber->Subscribe(a_eventType, a_handler);
}

} // smart_home
