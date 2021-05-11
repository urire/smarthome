#ifndef SABATO_MULTI_THREADED_HANDLER_HPP
#define SABATO_MULTI_THREADED_HANDLER_HPP

#include "ievent_handler.hpp"       // smart_home::IEventHandler
#include "event.hpp"                // smart_home::Event
#include "shared_ptr.hpp"	        // experis::SharedPtr
#include "semaphore.hpp"            // experis::Semaphore

using namespace experis;

namespace smart_home {

class MultiThreadedHandler : public IEventHandler {
public:
    typedef SharedPtr<Event> EventPtr;

    friend class Distributor;

public:
    // virtual void Handle(const SharedPtr<Event>& a_event) = 0;

    MultiThreadedHandler();
    virtual ~MultiThreadedHandler();

private: // for friends
    void Wait();    
    void MultiThreadedHandle(const EventPtr& a_event);

private:
    Semaphore m_notifier;

};

} // smart_home

#endif  // SABATO_MULTI_THREADED_HANDLER_HPP