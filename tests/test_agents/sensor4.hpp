#ifndef SABATO_SENSOR4_HPP
#define SABATO_SENSOR4_HPP

#include "sensor.hpp"			// smart_home::Sensor, smart_home::AgentDetails
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr

namespace smart_home {

class Sensor4 : public Sensor {
public:
	// ~Sensor4();

	Sensor4(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);
	
	virtual void Run();

};

} // smart_home

#endif	// SABATO_SENSOR4_HPP
