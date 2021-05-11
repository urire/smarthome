#include "distributor.hpp"      // smart_home::Distributor

using namespace experis;

namespace smart_home {

Distributor::DistributeCommand::DistributeCommand(Distributor& a_this, Semaphore& a_notifier, const EventPtr& a_event) 
: m_this(a_this)
, m_notifier(a_notifier)
, m_event(a_event) 
{	
}

void Distributor::DistributeCommand::Do() {		
	m_this.Distribute(m_event, m_notifier);		
}

Distributor::Distributor() 
: IUncopyable()
, m_router()
, m_typeCounters()
{
}

Distributor::~Distributor() {  
}

void Distributor::Distribute(const EventPtr& a_event, Semaphore& a_notifier) {
    HandlerContainer listeners;

    listen(listeners, a_event->Type());
	wait(listeners, a_notifier);
    notify(listeners, a_event);
}

void Distributor::Add(const EventType& a_type, const HandlerPtr& a_handle) {
	m_router[a_type].insert(a_handle);

	if(a_type.Name() != EventType::All()) {
		m_typeCounters.Add(a_type.Name(), SharedPtr<Semaphore>(new Semaphore(1)));
	}	
}

void Distributor::Remove(const HandlerPtr& a_handle) {
	for (HandlerMap::iterator itr = m_router.begin(); itr != m_router.end(); ++itr) {
		itr->second.erase(a_handle);
	}
}

void Distributor::listen(HandlerContainer& a_listeners, const EventType& a_type) {
	if(a_type.ContainsAll()) {
        return;
    }
    
    addListener(a_listeners, a_type);
	addListener(a_listeners, EventType(a_type.Name(), EventType::All(), a_type.Floor()));
	addListener(a_listeners, EventType(a_type.Name(), EventType::All(), EventType::All()));
	addListener(a_listeners, EventType(EventType::All(), a_type.Room(), a_type.Floor()));
	addListener(a_listeners, EventType(EventType::All(), EventType::All(), a_type.Floor()));
	addListener(a_listeners, EventType(EventType::All(), EventType::All(), EventType::All()));
}

void Distributor::addListener(HandlerContainer& a_listeners, const EventType& a_type) {
	HandlerMap::iterator itr = m_router.find(a_type);
	
	if (itr != m_router.end()) {
		a_listeners.insert(a_listeners.end(), itr->second.begin(), itr->second.end());
	}
}

void Distributor::wait(HandlerContainer& a_listeners, Semaphore& a_notifier) {
	for(size_t i = 0; i < a_listeners.size(); ++i) {
		a_listeners[i]->Wait();
	}

	a_notifier.Post();
}

void Distributor::notify(HandlerContainer& a_listeners, const EventPtr& a_event) {
	Semaphore& typeCounter = m_typeCounters.Get(a_event->Type().Name());
	
	typeCounter.Wait();
	
	for(size_t i = 0; i < a_listeners.size(); ++i) {
        a_listeners[i]->MultiThreadedHandle(a_event);
    }

	typeCounter.Post();
}

} // smart_home
