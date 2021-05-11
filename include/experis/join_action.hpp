#ifndef THREAD_POOL_JOIN_ACTION_HPP
#define THREAD_POOL_JOIN_ACTION_HPP

#include "iaction.hpp"					// experis::IAction
#include "pool.hpp"						// experis::Pool
#include "rendezvous_point.hpp"			// experis::RendezvousPoint
#include "atomic.hpp"					// experis::Atomic

namespace experis {

class JoinAction : public IAction {
public:
	JoinAction(Pool& a_pool, Atomic<bool>& a_isAlive, RendezvousPoint& a_rendPoint);
	
	virtual void Perform();

private:
	Pool& m_pool;
	Atomic<bool>& m_isAlive;
	RendezvousPoint& m_rendPoint;
	
};

} // experis

#endif	// THREAD_POOL_JOIN_ACTION_HPP
