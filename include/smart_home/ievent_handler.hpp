#ifndef SABATO_IEVENT_HANDLER_HPP
#define SABATO_IEVENT_HANDLER_HPP

#include "event.hpp"        // smart_home::Event
#include "shared_ptr.hpp"	// experis::SharedPtr

using namespace experis;

namespace smart_home {

struct IEventHandler {
    // IEventHandler() = default;
    // IEventHandler(const IEventHandler&) = default;
    // IEventHandler& operator=(const IEventHandler&) = default;
    
    virtual ~IEventHandler() {}
    virtual void Handle(const SharedPtr<Event>& a_event) = 0;

};

} // smart_home

#endif  // SABATO_IEVENT_HANDLER_HPP
