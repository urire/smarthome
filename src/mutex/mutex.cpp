#include "mutex.hpp"

#include <assert.h>
#include <errno.h>

namespace experis {

Mutex::Mutex()
: IUnassignable()
, m_lock() 
{ 
	int statusCode = pthread_mutex_init(&m_lock, NULL);
	if(statusCode) {
		switch(statusCode) {
		case EAGAIN:
			throw NotEnoughResourceException(); 
			break;
		case ENOMEM:
			throw NotEnoughMemoryException(); 
			break;			
		case EBUSY:
		case EINVAL:	
		case EPERM:
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

Mutex::Mutex(const Mutex& a_other)
: IUnassignable()
, m_lock(a_other.m_lock) 
{
}

Mutex::~Mutex() { 
	pthread_mutex_destroy(&m_lock);	
}

void Mutex::Lock() {
	int statusCode = pthread_mutex_lock(&m_lock);
	if(statusCode) {
		switch(errno) {
		case EDEADLK:
			throw AlreadyLockedException(); 
			break;
		case EINVAL:
		case EAGAIN:	
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		} 
	}
}

void Mutex::UnLock() { 
	int statusCode = pthread_mutex_unlock(&m_lock);	
	if(statusCode) {
		switch(errno) {
		case EPERM:
		case EINVAL:
		case EAGAIN:	
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	} 
}

} // experis
