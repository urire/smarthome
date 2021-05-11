#ifndef EXPERIS_RENDEZVOUS_POINT_HPP
#define EXPERIS_RENDEZVOUS_POINT_HPP

#include "mutex.hpp"                    // experis::Mutex              
#include "iuncopyable.hpp"              // experis::IUncopyable
#include "condition_variable.hpp"       // experis::ConditionVariable

namespace experis {

class RendezvousPoint : private IUncopyable {
public:
    // RendezvousPoint() = delete;
    // ~RendezvousPoint() = default;

    RendezvousPoint(Mutex& a_lock, ConditionVariable& a_notifier);

    void Notify();
    void Wait();

private:
    Mutex& m_lock;
    ConditionVariable& m_notifier;
    bool m_arrived;

};

} // experis

#endif  // EXPERIS_RENDEZVOUS_POINT_HPP 