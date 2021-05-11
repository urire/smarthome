#ifndef SABATO_SUBSCRIBER_HPP
#define SABATO_SUBSCRIBER_HPP

#include "isubscriber.hpp"		// smart_home::ISubscriber
#include "extractor.hpp"		// smart_home::Extractor

using namespace experis;

namespace smart_home {

class Subscriber : public ISubscriber {
public:
	// Subscriber() = delete;
	// ~Subscriber() = default;

    Subscriber(Extractor& a_extractor);

	virtual void Subscribe(const EventType& a_eventType, const HandlerPtr& a_handler);
	
private:
	Extractor& m_extractor;

};

} // smart_home

#endif	// SABATO_SUBSCRIBER_HPP
