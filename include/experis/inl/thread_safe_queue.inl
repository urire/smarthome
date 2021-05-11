#ifndef EXPERIS_THREAD_SAFE_QUEUE_INL
#define EXPERIS_THREAD_SAFE_QUEUE_INL

#include <assert.h>							// assert

namespace experis {

template<typename T>
class PredFull {
public:
	PredFull(ThreadSafeQueue<T>& a_queue);
	
	bool operator()();

private:
	ThreadSafeQueue<T>& m_queue;

};

template<typename T>
class PredEmpty {
public:
	PredEmpty(ThreadSafeQueue<T>& a_queue);
	
	bool operator()();

private:
	ThreadSafeQueue<T>& m_queue;

};

template<typename T>
PredFull<T>::PredFull(ThreadSafeQueue<T>& a_queue)
: m_queue(a_queue) 
{
}

template<typename T>
bool PredFull<T>::operator()() {
	return m_queue.isFullAndRunning();
}

template<typename T>
PredEmpty<T>::PredEmpty(ThreadSafeQueue<T>& a_queue)
: m_queue(a_queue) 
{
}

template<typename T>
bool PredEmpty<T>::operator()() {
	return m_queue.isEmpty() && !m_queue.m_shutting;
}

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(size_t a_capacity)
: IUncopyable()
, m_items()
, m_queueLock()
, m_notFull()
, m_notEmpty()
, m_capacity(a_capacity)
, m_enqWaiter(0) 
, m_deqWaiter(0)
, m_shutting(false) 
, m_shutdownLock()
, m_shutdownNotifier()
, m_shutdownPoint(m_shutdownLock, m_shutdownNotifier)
{	
	if(0 == m_capacity) {
		throw ContainerSizeIsZeroException();
	}
}

template<typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue() {	
	AwaitShutdown();	
}

template<typename T>
bool ThreadSafeQueue<T>::Enqueue(const T& a_item) {
	bool enqueued = false;
	
	if(m_shutting) {
		signalShoutdownIfNeeded();
		return enqueued;
	}
	
	{
		PredFull<T> pred(*this);
		Guard guard(m_queueLock);
		
		++m_enqWaiter;
		m_notFull.Wait(m_queueLock, pred);
		--m_enqWaiter;		
		
		if(m_shutting) {
			signalShoutdownIfNeeded();
			return enqueued;
		}

		enqueued = true;

		m_items.push(a_item);		
	}
	
	if(m_deqWaiter) {
		m_notEmpty.Signal();
	}	

	return enqueued;
}

template<typename T>
bool ThreadSafeQueue<T>::Dequeue(T& a_item) {
	return dequeue(&a_item);
}

template<typename T>
bool ThreadSafeQueue<T>::Dequeue() {
	return dequeue(NULL);
}

template<typename T>
void ThreadSafeQueue<T>::Clear() {
	Guard guard(m_queueLock);

	while(!m_items.empty()) {
		m_items.pop();
	}

	m_notFull.Signal();
}

template<typename T>
void ThreadSafeQueue<T>::AsyncShutdown() {
	Guard guard(m_queueLock);

	m_shutting = true;	

	if(m_enqWaiter) {
		m_notFull.Broadcast();
	}
	
	if(m_deqWaiter) {
		m_notEmpty.Broadcast();
	}
}

template<typename T>
void ThreadSafeQueue<T>::AwaitShutdown() {
	AsyncShutdown();
	waitShoutdownIfNeeded();
}

template<typename T>
size_t ThreadSafeQueue<T>::Size() const {
	Guard guard(m_queueLock);
	
	return m_items.size();
}

template<typename T>
bool ThreadSafeQueue<T>::IsEmpty() const {
	Guard guard(m_queueLock);
	
	return isEmpty();
}

template<typename T>
bool ThreadSafeQueue<T>::IsFull() const {
	Guard guard(m_queueLock);
	
	return m_capacity == m_items.size();
}

template<typename T>
bool ThreadSafeQueue<T>::dequeue(T* a_item) {
	bool dequeued = false;
	
	if(m_shutting) {
		signalShoutdownIfNeeded();
		return dequeued;
	}

	{
		PredEmpty<T> pred(*this);
		Guard guard(m_queueLock);
		
		++m_deqWaiter;
		m_notEmpty.Wait(m_queueLock, pred);
		--m_deqWaiter;

		if(m_shutting) {
			signalShoutdownIfNeeded();
			return dequeued;
		}

		dequeued = true;
		
		if(a_item) {
			*a_item = m_items.front();
		}
		
		m_items.pop();

		if(m_enqWaiter) {
			m_notFull.Signal();
		}
	}

	return dequeued;
}

template<typename T>
bool ThreadSafeQueue<T>::isFullAndRunning() const {
	return m_capacity == m_items.size() && !m_shutting;
}

template<typename T>
bool ThreadSafeQueue<T>::isEmpty() const {
	return 0 == m_items.size();
}

template<typename T>
void ThreadSafeQueue<T>::waitShoutdownIfNeeded() {
	Guard guard(m_shutdownLock);

	if(m_enqWaiter || m_deqWaiter) {
		m_shutdownPoint.Wait();
	}
}

template<typename T>
void ThreadSafeQueue<T>::signalShoutdownIfNeeded() {
	if(m_enqWaiter + m_enqWaiter == 0) {
		m_shutdownPoint.Notify();
	}
}

} // experis

#endif // EXPERIS_THREAD_SAFE_QUEUE_INL
