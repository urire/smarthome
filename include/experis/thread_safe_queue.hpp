#ifndef EXPERIS_THREAD_SAFE_QUEUE_HPP
#define EXPERIS_THREAD_SAFE_QUEUE_HPP

#include "iuncopyable.hpp"			// experis::IUncopyable
#include "mutex.hpp"				// experis::Mutex
#include "guard.hpp"				// experis::Guard
#include "condition_variable.hpp"	// experis::ConditionVariable
#include "rendezvous_point.hpp"		// experis::RendezvousPoint
#include <exception>				// std::exception
#include <queue>					// std::queue
#include <stddef.h>					// size_t

namespace experis {

template<typename T>
class ThreadSafeQueue : private IUncopyable {
public:
	template<typename S>
	friend class PredFull;
	
	template<typename S>
	friend class PredEmpty;

	struct ContainerSizeIsZeroException : public std::exception {};

public:
	ThreadSafeQueue(size_t a_capacity = 100);
	~ThreadSafeQueue();	
	
	bool Enqueue(const T& a_item);
	bool Dequeue(T& a_item);
	bool Dequeue();	
	void Clear();	
	void AsyncShutdown();
	void AwaitShutdown();
	size_t Size() const;
	bool IsEmpty() const;
	bool IsFull() const;

private: // for friends
	bool isFullAndRunning() const;
	bool isEmpty() const;
	void waitShoutdownIfNeeded();
	void signalShoutdownIfNeeded();

private:
	bool dequeue(T* a_item);	

private:
	std::queue<T> m_items;
	mutable Mutex m_queueLock;
	ConditionVariable m_notFull;	
	ConditionVariable m_notEmpty;
	const size_t m_capacity;
	size_t m_enqWaiter;	
	size_t m_deqWaiter;
	bool m_shutting;
	mutable Mutex m_shutdownLock;
	ConditionVariable m_shutdownNotifier;
	RendezvousPoint m_shutdownPoint;

};

} // experis

#include "inl/thread_safe_queue.inl"

#endif	// EXPERIS_THREAD_SAFE_QUEUE_HPP
