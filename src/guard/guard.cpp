#include "guard.hpp"

namespace experis {

Guard::Guard(Mutex& a_lock) 
: IUncopyable()
, m_lock(a_lock) 
{ 
	m_lock.Lock(); 
}

Guard::~Guard() { 
	m_lock.UnLock(); 
}

} // experis
