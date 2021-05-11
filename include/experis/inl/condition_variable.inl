#ifndef EXPERIS_CONDITION_VARIABLE_INL
#define EXPERIS_CONDITION_VARIABLE_INL

#include <assert.h>			// assert
#include <errno.h>			// errno

namespace experis {

template<typename Predicate>
void ConditionVariable::Wait(Mutex& a_mtx, Predicate a_predicate) {
	while(a_predicate()) {
		int statusCode = pthread_cond_wait(&m_condition, &a_mtx.m_lock);
		if(statusCode) {
			switch(errno) {
			case EINVAL:
				throw WaitOnDifferentMutexException(); 
				break;
			case EPERM:			
				assert("Impossible errno code");
				break;		
			default:
				assert("Undocumented errno code");
			}
		}
	}
}

} // experis

#endif	// EXPERIS_CONDITION_VARIABLE_INL
