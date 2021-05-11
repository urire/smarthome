#ifndef SABATO_HVAC_CONTROLLER_HPP
#define SABATO_HVAC_CONTROLLER_HPP

#include "controller.hpp"		// smart_home::Controller, smart_home::AgentDetails
#include "event.hpp"            // smart_home::Event
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr

using namespace experis;

namespace smart_home {

class HVACController : public Controller {
public:
	// ~HVACController();

	HVACController(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);
	
private:
	int m_temp;
	
};

} // smart_home

#endif	// SABATO_HVAC_CONTROLLER_HPP
