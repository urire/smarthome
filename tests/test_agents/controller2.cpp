#include "controller2.hpp"      // smart_home::Controller2
#include "definitions.hpp"      // CONTROLLER1_EVENT_TYPE
#include <string>               // std::string
#include <assert.h>             // assert    

namespace smart_home {

struct ControllerHandler : public MultiThreadedHandler {
    ControllerHandler(Controller2& a_this);

    virtual void Handle(const Controller::EventPtr& a_event);

private:
    Controller2& m_this;

};

ControllerHandler::ControllerHandler(Controller2& a_this)
: MultiThreadedHandler()
, m_this(a_this)
{
}

void ControllerHandler::Handle(const Controller::EventPtr& a_event) {
    assert(a_event->Type().Name() == "1");
    m_this.Log("1");
}

struct ControllerHandler1 : public MultiThreadedHandler {
    ControllerHandler1(Controller2& a_this);

    virtual void Handle(const Controller::EventPtr& a_event);

private:
    Controller2& m_this;

};

ControllerHandler1::ControllerHandler1(Controller2& a_this)
: MultiThreadedHandler()
, m_this(a_this)
{
}

void ControllerHandler1::Handle(const Controller::EventPtr& a_event) {
    assert(a_event->Type().Name() == "2");
    m_this.Log("2");
}

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new Controller2(a_mediator, a_details));
}

Controller2::Controller2(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Controller(a_mediator, a_details) 
{
    Subscribe(EventType("1", "2", "2"), HandlerPtr(new ControllerHandler(*this)));
    Subscribe(EventType("2", "2", "2"), HandlerPtr(new ControllerHandler1(*this)));
}

} // smart_home
