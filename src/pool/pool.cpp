#include "pool.hpp"		// experis::Pool
#include <stddef.h>		// size_t

namespace experis {

Pool::Pool(RendezvousPoint& a_rendPoint)
: IUncopyable()
, m_threads()
, m_rendPoint(a_rendPoint)
, m_joinerThread() {
}

void Pool::AddJoiner(const SharedPtr<IAction>& a_action) {
	m_joinerThread = SharedPtr<OldThread>(new OldThread(*a_action));
	m_joinerThread->Start();
}

void Pool::Add(const SharedPtr<IAction>& a_action) {
	m_threads.push_back(SharedPtr<CompletionAwareThread>(new CompletionAwareThread(a_action, m_rendPoint)));
}

std::vector<SharedPtr<CompletionAwareThread> >& Pool::Threads() {
	return m_threads;
}

} // experis
