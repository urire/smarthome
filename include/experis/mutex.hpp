#ifndef EXPERIS_MUTEX_HPP
#define EXPERIS_MUTEX_HPP

#include "iunassignable.hpp"	// experis::IUnassignable
#include <exception>			// std::exception
#include <pthread.h>			// pthread_mutex_t

namespace experis {

class Mutex : private IUnassignable {
public:
	friend class ConditionVariable;

	struct NotEnoughResourceException : public std::exception {};
	struct NotEnoughMemoryException : public std::exception {};
	struct AlreadyLockedException : public std::exception {};

public:
	Mutex();
	Mutex(const Mutex& a_other);				
	~Mutex();
	
	void Lock();	
	void UnLock();

private:
	pthread_mutex_t m_lock;
	
};

} // experis

#endif	// EXPERIS_MUTEX_HPP
