#include "condition_variable.hpp"		// experis::ConditionVariable
#include <pthread.h>					// pthread_cond_init, pthread_cond_destroy, pthread_cond_wait, pthread_cond_signal, pthread_cond_broadcast
#include <cstddef>						// NULL
#include <assert.h>						// assert
#include <errno.h>						// errno

namespace experis {

ConditionVariable::ConditionVariable()
: m_condition() 
{
	int statusCode = pthread_cond_init(&m_condition, NULL);	
	if(statusCode) {
		switch(errno) {
		case EAGAIN:
			throw NotEnoughResourceException(); 
			break;
		case ENOMEM:
			throw NotEnoughMemoryException(); 
			break;
		case EBUSY:
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

ConditionVariable::~ConditionVariable() {
	int statusCode = pthread_cond_destroy(&m_condition);
	if(statusCode) {
		switch(errno) {
		case EBUSY:
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

void ConditionVariable::Signal() {
	int statusCode = pthread_cond_signal(&m_condition);
	if(statusCode) {
		switch(errno) {
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

void ConditionVariable::Broadcast() {
	int statusCode = pthread_cond_broadcast(&m_condition);
	if(statusCode) {
		switch(errno) {
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

} // experis
