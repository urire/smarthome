#ifndef EXPERIS_THREAD_POOL_HPP
#define EXPERIS_THREAD_POOL_HPP

#include "command.hpp"						// experis::Command
#include "iaction.hpp"						// experis::IAction
#include "join_action.hpp"					// experis::JoinAction
#include "thread_safe_queue.hpp"			// experis::ThreadSafeQueue
#include "pool.hpp"							// experis::Pool
#include "blocker.hpp"						// experis::Blocker
#include "tp_looper.hpp"					// experis::TPLooper
#include "iuncopyable.hpp"					// experis::IUncopyable
#include "shared_ptr.hpp"					// experis::SharedPtr
#include "semaphore.hpp"					// experis::Semaphore
#include "condition_variable.hpp"			// experis::ConditionVariable, experis::Mutex
#include "rendezvous_point.hpp"				// experis::RendezvousPoint
#include "atomic.hpp"         				// experis::Atomic
#include <exception>						// std::exception
#include <vector>							// std::vector
#include <stddef.h>							// size_t

namespace experis {

class ThreadPool : private IUncopyable {	
public:	
	struct DecreaseWithZeroThreadsException : public std::exception {};
	
public:
	ThreadPool(size_t a_numThreads);
	~ThreadPool();
	
	void Add(const SharedPtr<Command>& a_cmd);
	void Pause();
	void Resume();
	void IncThreads();
	void DecThreads();	
	size_t ActiveThreads() const;

private:
	ThreadSafeQueue<SharedPtr<Command> > m_commands;
	size_t m_activeThreads;
	std::vector<SharedPtr<IAction> > m_loopers;	
	ConditionVariable m_cv;
	Mutex m_mtx;
	RendezvousPoint m_randPoint;
	Atomic<bool> m_isAlive;
	Pool m_pool;
	SharedPtr<IAction> m_joiner;
	Semaphore m_unblocker;
	SharedPtr<Command> m_blocker;	
	
};

} // experis

#endif	// EXPERIS_THREAD_POOL_HPP
