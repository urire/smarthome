#include "thread.hpp"			// experis::Thread
#include "guard.hpp"			// experis::Guard
#include <signal.h>				// pthread_kill
#include <cassert>				// assert
#include <errno.h>				// errno

namespace experis {

Thread::Thread(SharedPtr<IAction> a_action) 
: IUncopyable()
, m_lock()
, m_thread()
, m_notifier() 
, m_action(a_action)
, m_canJoinOrDetach(true)
, m_rendezvousPoint(m_lock, m_notifier)
{
	start();
}

Thread::~Thread() {
	Guard guard(m_lock);

	if(m_canJoinOrDetach) {
		assert(!"user did not join or detach the thread");
	}
}

void Thread::Join() {
	Guard guard(m_lock);
	
	if(m_canJoinOrDetach) {
		int statusCode = pthread_join(m_thread, NULL);
		if(statusCode) {
			switch(errno) {
			case EDEADLK:
				throw DeadLockException(); 
				break;
			case EINVAL:	
			case ESRCH:			
				assert("Impossible errno code");
				break;		
			default:
				assert("Undocumented errno code");
			}
		}
		
		m_canJoinOrDetach.Clear();
	}
}

void Thread::Detach() {
	Guard guard(m_lock);
	
	if(m_canJoinOrDetach) {
		int statusCode = pthread_detach(m_thread);	
		if(statusCode) {
			switch(errno) {
			case EINVAL:	
			case ESRCH:			
				assert("Impossible errno code");
				break;		
			default:
				assert("Undocumented errno code");
			}
		}
		
		m_canJoinOrDetach.Clear();
	}
}

void Thread::Cancel() {
	Guard guard(m_lock);
	
	if(m_canJoinOrDetach) {
		int statusCode = pthread_cancel(m_thread);	
		if(statusCode) {
			switch(errno) {
			case ESRCH:			
				assert("Impossible errno code");
				break;		
			default:
				assert("Undocumented errno code");
			}
		}
	
		m_canJoinOrDetach.Clear();
	}
}

void Thread::Kill(int a_sig) {
	Guard guard(m_lock);
	
	if(m_canJoinOrDetach) {
		int statusCode = pthread_kill(m_thread, a_sig);	
		if(statusCode) {
			switch(errno) {
			case EINVAL:			
				throw InvalidSignalException(); 
				break;		
			default:
				assert("Undocumented errno code");
			}
		}
	
		m_canJoinOrDetach.Clear();
	}
}

void Thread::Yield() {
	int statusCode = pthread_yield();	
	if(statusCode) {
		switch(errno) {	
		default:
			assert("Undocumented errno code");
		}
	}
}

void Thread::Exit() {
	pthread_exit(0);	
}

void* Thread::threadFunction(void* a_context) {
	assert(a_context);

	Context* context = static_cast<Context*>(a_context);
	Thread* thread = context->first;
	SharedPtr<IAction> action = *context->second;
		
	thread->m_rendezvousPoint.Notify();
	
	try {
		action->Perform();
	}
	catch(const std::exception& ex) {
		assert(!"routine provided to thread was corrupted");
	}
	catch(...) {
		assert(!"routine provided to thread was corrupted");
	}

	return NULL;	
}

void Thread::start() {
	Context context = std::make_pair(this, &m_action);

	int statusCode = pthread_create(&m_thread, NULL, threadFunction, &context);	
	if(statusCode) {
		switch(errno) {
		case EAGAIN:
			throw NotEnoughResourceException(); 
			break;
		case EINVAL:	
		case EPERM:			
			assert("Impossible errno code");
			break;		
		default:
			assert("Undocumented errno code");
		}
	}
	
	m_rendezvousPoint.Wait();
}

} // experis
