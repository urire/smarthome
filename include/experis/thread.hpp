#ifndef EXPERIS_THREAD_HPP
#define EXPERIS_THREAD_HPP

#include "condition_variable.hpp"	// experis::ConditionVariable
#include "rendezvous_point.hpp"     // experis::RendezvousPoint
#include "iuncopyable.hpp"			// experis::IUncopyable
#include "shared_ptr.hpp"			// experis::SharedPtr
#include "iaction.hpp"				// experis::IAction
#include "atomic.hpp"				// experis::Atomic
#include "mutex.hpp"				// experis::Mutex
#include <exception>				// std::exception
#include <utility>      			// std::pair
#include <pthread.h>				// pthread_t

namespace experis {

class Thread : private IUncopyable {
public:
	typedef std::pair<Thread*, SharedPtr<IAction>*> Context;

	struct DeadLockException : public std::exception {};
	struct InvalidSignalException : public std::exception {};
	struct NotEnoughResourceException : public std::exception {};		

public:	
	// Thread() = delete;

	Thread(SharedPtr<IAction> a_action);	
	virtual ~Thread();	
	
	void Join();
	void Detach();	
	void Cancel();
	void Kill(int a_sig);	

public:
	static void Yield();
	static void Exit();

private:
	static void* threadFunction(void* a_action);

private:
	void start();

private:
	mutable Mutex m_lock;
	pthread_t m_thread;
	ConditionVariable m_notifier;
	SharedPtr<IAction> m_action;	
	Atomic<bool> m_canJoinOrDetach;
	RendezvousPoint m_rendezvousPoint;
	
};

} // experis

#endif	// EXPERIS_THREAD_HPP
