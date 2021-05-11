#include "blocker.hpp"		// experis::Blocker

namespace experis {

Blocker::Blocker(Semaphore& a_blockedItems)
: m_blockedItems(a_blockedItems) {
}

void Blocker::Do() {
	m_blockedItems.Wait();
}

} // experis
