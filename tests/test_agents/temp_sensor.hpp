#ifndef SABATO_TEMP_SENSOR_HPP
#define SABATO_TEMP_SENSOR_HPP

#include "sensor.hpp"			// smart_home::Sensor, smart_home::AgentDetails
#include "mediator.hpp"			// smart_home::Mediator
#include "shared_ptr.hpp"       // experis::SharedPtr
#include <string>				// std::string
#include <cstddef>				// size_t

namespace smart_home {

class TempSensor : public Sensor {
public:
	TempSensor(const SharedPtr<Mediator>& a_mediator, const AgentDetails& a_details);	
	
	virtual void Run();
	
private:
	int m_lower;
	int m_upper;
	size_t m_period;
	std::string m_units;

};

} // smart_home

#endif	// SABATO_TEMP_SENSOR_HPP
