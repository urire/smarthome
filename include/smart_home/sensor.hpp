#ifndef SABATO_SENSOR_HPP
#define SABATO_SENSOR_HPP

#include "agent.hpp"            // smart_home::Agent, smart_home::AgentDetails
#include "mediator.hpp"			// smart_home::Mediator
#include "ipublisher.hpp"       // smart_home::IPublisher
#include "thread.hpp"		    // experis::Thread, experis::IAction

using namespace experis;

namespace smart_home {

class Sensor : public Agent, public IPublisher {
public:
    typedef SharedPtr<IAction> ActionPtr;
    typedef SharedPtr<Thread> ThreadPtr;
    typedef SharedPtr<IPublisher> PublisherPtr;

public:
    // Sensor() = delete;
    // Sensor(const Sensor&) = delete;
    // Sensor& operator=(const Sensor&) = delete;
    // virtual void Log(const std::string& a_msgToLog);

	Sensor(const MediatorPtr& a_mediator, const AgentDetails& a_details, bool a_usingThread = false);
    virtual ~Sensor();
    
    virtual void Publish(const EventPtr& a_event);     
    virtual void Start(); 
    virtual void Shutdown(); 
    virtual void Run() = 0; 

private:
    PublisherPtr m_publisher;
    ActionPtr m_action;
	ThreadPtr m_thread;
	bool m_usingThread;

};

} // smart_home

#endif  // SABATO_SENSOR_HPP