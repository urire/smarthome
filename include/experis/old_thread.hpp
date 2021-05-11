#ifndef THREAD_POOL_OLD_THREAD_HPP
#define THREAD_POOL_OLD_THREAD_HPP

#include "iunassignable.hpp"	// experis::IUnassignable
#include "iaction.hpp"			// experis::IAction
#include <pthread.h>			// pthread_t
#include <exception>			// std::exception

namespace experis {

class OldThread : private IUnassignable {
public:	
	struct NotEnoughMemoryException : public std::exception {};
	struct NotJoinableThreadException : public std::exception {};

public:	
	// OldThread() = delete;

	OldThread(const IAction& a_action);
	OldThread(const OldThread& a_other);	
	
	virtual ~OldThread();	
	
	void Start();
	void Detach();		
	
private:
	static void* handle(void* a_this);

private:
	pthread_t m_thread;
	IAction* m_action;
	
};

} // experis

#endif	// THREAD_POOL_OLD_THREAD_HPP
