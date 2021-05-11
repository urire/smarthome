#include "old_thread.hpp"		// experis::OldThread
#include <assert.h>				// assert
#include <errno.h>				// errno

namespace experis {

OldThread::OldThread(const IAction& a_action) 
: IUnassignable()
, m_action(const_cast<IAction*>(&a_action)) {
}

OldThread::OldThread(const OldThread& a_other)
: IUnassignable()
, m_thread(a_other.m_thread)
, m_action(a_other.m_action) {
}

OldThread::~OldThread() {
	int statusCode = pthread_join(m_thread, NULL);
	assert(0 == statusCode);
}

void OldThread::Start() {
	int statusCode = pthread_create(&m_thread, NULL, handle, m_action);	
	if(statusCode) {
		switch(errno) {
		case EAGAIN:
			throw NotEnoughMemoryException(); 
			break;
		case EINVAL:	
		case EPERM:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

void OldThread::Detach() {
	int statusCode = pthread_detach(m_thread);	
	if(statusCode) {
		switch(errno) {
		case EINVAL:
			throw NotJoinableThreadException(); 
			break;	
		case ESRCH:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
}

void* OldThread::handle(void* a_this) {
	reinterpret_cast<IAction*>(a_this)->Perform();
	return NULL;	
}

} // experis
