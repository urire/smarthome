#include "join_action.hpp"		// experis::JoinAction

namespace experis {

JoinAction::JoinAction(Pool& a_pool, Atomic<bool>& a_isAlive, RendezvousPoint& a_rendPoint)
: m_pool(a_pool)
, m_isAlive(a_isAlive)
, m_rendPoint(a_rendPoint) {
}

void JoinAction::Perform() {
	while(m_isAlive == true) {
		m_rendPoint.Wait();
		
		if(!m_isAlive) {
			break;
		}
		
		std::vector<SharedPtr<CompletionAwareThread> >& threads = m_pool.Threads();
		std::vector<SharedPtr<CompletionAwareThread> >::iterator itr = threads.begin();
		std::vector<SharedPtr<CompletionAwareThread> >::iterator end = threads.end();
		while(itr != end) {
			if((*itr)->IsAlive()) {
				++itr;				
			}
			else {
				itr = threads.erase(itr);
			}
		}
	}	
}

} // experis
