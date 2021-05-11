#ifndef SABATO_SENSOR2_HPP
#define SABATO_SENSOR2_HPP

#include "sensor.hpp"			// smart_home::Sensor, smart_home::AgentDetails
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr

namespace smart_home {

class Sensor2 : public Sensor {
public:
	// ~Sensor2();

	Sensor2(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);
	
	virtual void Run();

};

} // smart_home

#endif	// SABATO_SENSOR2_HPP
