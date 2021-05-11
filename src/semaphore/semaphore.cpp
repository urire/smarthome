#include "semaphore.hpp"		// experis::Semaphore
#include <assert.h>				// assert
#include <errno.h>				// errno

namespace experis {

Semaphore::Semaphore(size_t a_size)
: IUnassignable() {
	int statusCode = sem_init(&m_semaphore, 0, a_size);	
	if(0 == statusCode) {
		switch(errno) {
		case EINVAL:
			throw ValueOutOfRangeException(); 
			break;
		case ENOSYS:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

Semaphore::Semaphore(const Semaphore& a_other) 
: IUnassignable()
, m_semaphore(a_other.m_semaphore) {
}
	
Semaphore::~Semaphore() {
	int statusCode = sem_destroy(&m_semaphore);
	assert(0 == statusCode);
}

void Semaphore::Wait() {	
	int statusCode = sem_wait(&m_semaphore);
	if(0 == statusCode) {
		switch(errno) {
		case EINTR:
			throw SignalInterruptException(); 
			break;
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}
	
void Semaphore::Post() {
	int statusCode = sem_post(&m_semaphore);

	if(0 == statusCode) {
		switch(errno) {
		case EOVERFLOW:
			throw OverflowException(); 
			break;
		case EINVAL:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

} // experis
