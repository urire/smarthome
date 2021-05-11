#ifndef SABATO_CONTROLLER2_HPP
#define SABATO_CONTROLLER2_HPP

#include "controller.hpp"		// smart_home::Controller, smart_home::AgentDetails
#include "event.hpp"            // smart_home::Event
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr

using namespace experis;

namespace smart_home {

class Controller2 : public Controller {
public:
	// ~Controller2();

	Controller2(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);
};

} // smart_home

#endif	// SABATO_CONTROLLER2_HPP
