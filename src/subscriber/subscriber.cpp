#include "subscriber.hpp"       // smart_home::Subscriber

namespace smart_home {

Subscriber::Subscriber(Extractor& a_extractor)
: m_extractor(a_extractor)
{
}

void Subscriber::Subscribe(const EventType& a_eventType, const HandlerPtr& a_handler) {
    m_extractor.Add(a_eventType, a_handler);
}

} // smart_home
