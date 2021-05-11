#include "multi_threaded_handler.hpp"       // smart_home::MultiThreadedHandler

using namespace experis;

namespace smart_home {

MultiThreadedHandler::MultiThreadedHandler() 
: m_notifier(1) 
{   
}

MultiThreadedHandler::~MultiThreadedHandler() {
}

void MultiThreadedHandler::Wait() {
    m_notifier.Wait();
}

void MultiThreadedHandler::MultiThreadedHandle(const EventPtr& a_event) {
    Handle(a_event);
    m_notifier.Post();
}

} // smart_home