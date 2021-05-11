#include "controller1.hpp"      // smart_home::Controller1
#include "definitions.hpp"      // CONTROLLER1_EVENT_TYPE
#include <string>               // std::string
#include <assert.h>             // assert    

namespace smart_home {

struct ControllerHandler : public MultiThreadedHandler {
    ControllerHandler(Controller1& a_this);

    virtual void Handle(const Controller::EventPtr& a_event);

private:
    Controller1& m_this;

};

ControllerHandler::ControllerHandler(Controller1& a_this)
: MultiThreadedHandler()
, m_this(a_this)
{
}

void ControllerHandler::Handle(const Controller::EventPtr& a_event) {
    assert(a_event->Type().Name() == CONTROLLER1_EVENT_TYPE);
    m_this.Log("test");
}

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new Controller1(a_mediator, a_details));
}

Controller1::Controller1(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Controller(a_mediator, a_details) 
{
    Subscribe(EventType(CONTROLLER1_EVENT_TYPE, "2", "2"), HandlerPtr(new ControllerHandler(*this)));
}

} // smart_home
