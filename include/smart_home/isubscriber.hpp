#ifndef SABATO_ISUBSCRIBER_HPP
#define SABATO_ISUBSCRIBER_HPP

#include "multi_threaded_handler.hpp"   // smart_home::MultiThreadedHandler
#include "event_type.hpp"               // smart_home::EventType
#include "iuncopyable.hpp"		        // experis::IUncopyable
#include "shared_ptr.hpp"               // experis::SharedPtr

using namespace experis;

namespace smart_home {

class ISubscriber : private IUncopyable {
public:
    typedef SharedPtr<MultiThreadedHandler> HandlerPtr;

public:
	// ISubscriber() = default;

    virtual ~ISubscriber() {}

	virtual void Subscribe(const EventType& a_eventType, const HandlerPtr& a_handler) = 0;

};

} // smart_home

#endif	// SABATO_ISUBSCRIBER_HPP
