#include "sensor.hpp"		// smart_home::Sensor

namespace smart_home {

class SensorAction : public IAction {
public:
	SensorAction(Sensor& a_this);
	
	virtual void Perform();

private:
	Sensor& m_this;

};

SensorAction::SensorAction(Sensor& a_this)
: m_this(a_this) 
{	
}

void SensorAction::Perform() { 
	m_this.Run(); 
}

Sensor::Sensor(const MediatorPtr& a_mediator, const AgentDetails& a_details, bool a_usingThread) 
: Agent(a_mediator, a_details)
, m_publisher(a_mediator->GetPublisher())
, m_action()
, m_thread()
, m_usingThread(a_usingThread)
{
	if(m_usingThread) {
		m_action = ActionPtr(new SensorAction(*this));
	}
}

Sensor::~Sensor() { 
     Shutdown();
}

void Sensor::Publish(const EventPtr& a_event) {
    m_publisher->Publish(a_event);
}

void Sensor::Start() {
	if(m_usingThread){
		m_thread = ThreadPtr(new Thread(m_action));
	}	
}

void Sensor::Shutdown() {
	if(m_usingThread && !m_thread.IsNull()) {
		m_thread->Join();
		m_usingThread = false;
	}
}

} // smart_home
