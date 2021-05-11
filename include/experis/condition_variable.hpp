#ifndef EXPERIS_CONDITION_VARIABLE_HPP
#define EXPERIS_CONDITION_VARIABLE_HPP

#include "mutex.hpp"			// experis::Mutex
#include "iunassignable.hpp"	// experis::IUnassignable
#include <exception>			// std::exception
#include <pthread.h>			// pthread_cond_t

namespace experis {

class ConditionVariable : private IUnassignable {
public:	
	struct WaitOnDifferentMutexException : public std::exception {};
	struct NotEnoughResourceException : public std::exception {};	
	struct NotEnoughMemoryException : public std::exception {};

public:	
	// ConditionVariable(const ConditionVariable&) = default;	
	
	ConditionVariable();				
	~ConditionVariable();
	
	template<typename Predicate>
	void Wait(Mutex& a_mtx, Predicate a_predicate);
	
	void Signal();
	void Broadcast();

private:
	pthread_cond_t m_condition;															

};

} // experis

#include "inl/condition_variable.inl"

#endif	// EXPERIS_CONDITION_VARIABLE_HPP
