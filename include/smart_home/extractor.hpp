#ifndef SABATO_EXTRACTOR_HPP
#define SABATO_EXTRACTOR_HPP

#include <cstddef>						// size_t
#include "event.hpp"					// smart_home::Event
#include "event_type.hpp"				// smart_home::EventType
#include "distributor.hpp"				// smart_home::Distributor
#include "multi_threaded_handler.hpp"   // smart_home::MultiThreadedHandler
#include "iuncopyable.hpp"				// experis::IUncopyable
#include "shared_ptr.hpp"       		// experis::SharedPtr
#include "atomic.hpp"					// experis::Atomic
#include "thread.hpp"					// experis::Thread, experis::IAction
#include "thread_safe_queue.hpp"		// experis::ThreadSafeQueue
#include "thread_pool.hpp"				// experis::ThreadPool, experis::Command
#include "semaphore.hpp"				// experis::Semaphore

using namespace experis;

namespace smart_home {

class Extractor : private IUncopyable {
public:
	typedef SharedPtr<IAction> ActionPtr;
	typedef SharedPtr<Thread> ThreadPtr;
	typedef SharedPtr<Event> EventPtr;
	typedef SharedPtr<MultiThreadedHandler> HandlerPtr;
	typedef ThreadSafeQueue<EventPtr> EventQueue;
	typedef Atomic<bool> Bool;

	struct ExtractAction : public IAction {
		ExtractAction(Extractor& a_this);
		
		virtual void Perform();

	private:
		Extractor& m_this;

	};

public:
	Extractor(EventQueue& a_events);
	~Extractor();

	void Add(const EventType& a_type, const HandlerPtr& a_handle);
	void Remove(const HandlerPtr& a_handle);
	void Start();
	void Shutdown();

private:
	void startExtracting();

private:
	static size_t s_threadAmount;

private:
	ThreadPool m_pool;
	EventQueue& m_events;
	Distributor m_distributor;
	Semaphore m_notifier;
	ActionPtr m_action;
	ThreadPtr m_thread;	
	Bool m_shutting;

};

} // smart_home

#endif	// SABATO_EXTRACTOR_HPP
