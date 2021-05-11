#ifndef THREAD_POOL_POOL_HPP
#define THREAD_POOL_POOL_HPP

#include "iaction.hpp"						// experis::IAction
#include "shared_ptr.hpp"					// experis::SharedPtr
#include "iuncopyable.hpp"					// experis::IUncopyable
#include "rendezvous_point.hpp"				// experis::RendezvousPoint
#include "completion_aware_thread.hpp"		// experis::CompletionAwareThread
#include "old_thread.hpp"					// experis::OldThread
#include <vector>							// std::vector
#include <stddef.h>							// size_t

namespace experis {

class Pool : private IUncopyable {
public:
	Pool(RendezvousPoint& a_rendPoint);
	
	void AddJoiner(const SharedPtr<IAction>& a_action);
	void Add(const SharedPtr<IAction>& a_action);
	std::vector<SharedPtr<CompletionAwareThread> >& Threads();

private:
	std::vector<SharedPtr<CompletionAwareThread> > m_threads;
	RendezvousPoint& m_rendPoint;
	SharedPtr<OldThread> m_joinerThread;
	
};

} // experis

#endif	// THREAD_POOL_POOL_HPP
