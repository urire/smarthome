#ifndef SABATO_CONTROLLER_HPP
#define SABATO_CONTROLLER_HPP

#include <list>                         // std::list
#include "agent.hpp"                    // smart_home::Agent
#include "multi_threaded_handler.hpp"   // smart_home::MultiThreadedHandler
#include "isubscriber.hpp"              // smart_home::ISubscriber
#include "mediator.hpp"			        // smart_home::Mediator

using namespace experis;

namespace smart_home {

class Controller : public Agent, public ISubscriber {
public:
    typedef SharedPtr<MultiThreadedHandler> HandlerPtr;
    typedef std::list<HandlerPtr> HandlerList;
    typedef SharedPtr<ISubscriber> SubscriberPtr;

public:
    // Controller() = delete;
    // Controller(const Controller&) = delete;
    // Controller& operator=(const Controller&) = delete;
    // virtual void Log(const std::string& a_msgToLog);

    Controller(const MediatorPtr& a_mediator, const AgentDetails& a_details);
    virtual ~Controller();

    virtual void Subscribe(const EventType& a_eventType, const HandlerPtr& a_handler);

private:
    SubscriberPtr m_subscriber;
    HandlerList m_subscribers;

};

} // smart_home

#endif  // SABATO_CONTROLLER_HPP
