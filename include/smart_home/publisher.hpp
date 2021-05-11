#ifndef SABATO_PUBLISHER_HPP
#define SABATO_PUBLISHER_HPP

#include "ipublisher.hpp"       	// smart_home::IPublisher
#include "thread_safe_queue.hpp"	// experis::ThreadSafeQueue

using namespace experis;

namespace smart_home {

class Publisher : public IPublisher {
public:
	typedef SharedPtr<Event> EventPtr;
	typedef ThreadSafeQueue<EventPtr> EventQueue;

public:
	// Publisher() = delete;
	// ~Publisher() = default;

	Publisher(EventQueue& a_events);
	
	virtual void Publish(const EventPtr& a_event);
	
private:
	EventQueue& m_events;
	
};

} // smart_home

#endif	// SABATO_PUBLISHER_HPP
