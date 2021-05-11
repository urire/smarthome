#ifndef SABATO_SENSOR5_HPP
#define SABATO_SENSOR5_HPP

#include "sensor.hpp"			// smart_home::Sensor, smart_home::AgentDetails
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr

namespace smart_home {

class Sensor5 : public Sensor {
public:
	// ~Sensor5();

	Sensor5(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);
	
	virtual void Run();

};

} // smart_home

#endif	// SABATO_SENSOR5_HPP
