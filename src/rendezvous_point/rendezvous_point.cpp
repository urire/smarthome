#include "rendezvous_point.hpp"     // experis::RendezvousPoint
#include "not_arrived.hpp"          // experis::NotArrived 
#include "guard.hpp"                // experis::Guard
#include <cassert>                  // assert

namespace experis {

 RendezvousPoint::RendezvousPoint(Mutex& a_lock, ConditionVariable& a_notifier)
 : IUncopyable()
 , m_lock(a_lock)
 , m_notifier(a_notifier)
 , m_arrived(false) 
{
}

void RendezvousPoint::Notify() {
    Guard guard(m_lock);

    m_arrived = true;
    m_notifier.Broadcast();
}

void RendezvousPoint::Wait() {
    Guard guard(m_lock);

    if(!m_arrived) {
        m_notifier.Wait(m_lock, NotArrived(m_arrived));
        assert(m_arrived);
    }
}

} // experis