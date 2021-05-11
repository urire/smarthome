#include "hvac_controller.hpp"  // smart_home::HVACController
#include "definitions.hpp"      // CONTROLLER1_EVENT_TYPE
#include <sstream>				// std::stringstream
#include <string>               // std::string
#include <assert.h>             // assert    

namespace smart_home {

struct TempHandler : public MultiThreadedHandler {
    TempHandler(HVACController& a_this);

    virtual void Handle(const Controller::EventPtr& a_event);

private:
    HVACController& m_this;

};

TempHandler::TempHandler(HVACController& a_this)
: MultiThreadedHandler()
, m_this(a_this)
, m_temp(25)
{
}

void TempHandler::Handle(const Controller::EventPtr& a_event) {
    std::stringstream ss(a_event->Payload());
    int temp;
    
    ss << temp;
    
    if(m_temp != temp) {
    	m_this.Log("the temperature is: " + a_event->Payload() + "turning on the air conditioning");
    }
    else {
    	m_this.Log("the temperature is: " + a_event->Payload() + "turning off the air conditioning");
    }
}

smart_home::Agent::AgentPtr CreateAgent(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details) {
    return Agent::AgentPtr(new HVACController(a_mediator, a_details));
}

HVACController::HVACController(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details)
: Controller(a_mediator, a_details) 
{
    Subscribe(EventType("TEMPERATURE_EVENT", Details().Room(), Details().Floor()), HandlerPtr(new TempHandler(*this)));
}

} // smart_home
