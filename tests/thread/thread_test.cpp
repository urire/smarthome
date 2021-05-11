#include "mu_test.h"

#include "thread.hpp"
#include "guard.hpp"
#include "rendezvous_point.hpp"
#include "condition_variable.hpp"

#define COUNTING 10000000

using namespace experis;

static Mutex g_mutex;
static Mutex g_mutexPoint;
static ConditionVariable g_cv;
static int g_number = 0;
static RendezvousPoint g_rendezvousPoint(g_mutex, g_cv);


struct ThreadAction : public IAction {
	virtual void Perform() {
		unsigned int i;

		for(i = 0; i < COUNTING; i++) {	
			Guard guard(g_mutex);
					
			g_number++; 												
		}
	}
};


struct ThreadActionSync : public IAction {
	virtual void Perform() {
		unsigned int i;

		for(i = 0; i < COUNTING; i++) {	
			Guard guard(g_mutexPoint);				
			g_number++; 												
		}
		
		g_rendezvousPoint.Notify();
	}
};


BEGIN_TEST(counting_to_20000000_with_2_threads_join_test) 
	Thread thread1(SharedPtr<IAction>(new ThreadAction()));
	Thread thread2(SharedPtr<IAction>(new ThreadAction()));
	
	thread1.Join();
	thread2.Join();
	
	TRACER << "thread_safe_queue_producer_consumer_test:" << g_number << '\n';
    ASSERT_THAT(g_number == 2 * COUNTING);
END_TEST

BEGIN_TEST(counting_to_20000000_with_2_threads_join_async_test) 
	g_number = 0;

	Thread thread1(SharedPtr<IAction>(new ThreadActionSync()));
	Thread thread2(SharedPtr<IAction>(new ThreadActionSync()));
	
	thread1.Join();
	thread2.Join();
	
	TRACER << "counting_to_20000000_with_2_threads_async_test:" << g_number << '\n';
    ASSERT_THAT(g_number == 2 * COUNTING);
END_TEST

BEGIN_TEST(counting_to_20000000_with_2_threads_detach_test) 
	g_number = 0;

	Thread thread1(SharedPtr<IAction>(new ThreadActionSync()));
	Thread thread2(SharedPtr<IAction>(new ThreadActionSync()));
	
	thread1.Detach();
	thread2.Detach();
	
	g_rendezvousPoint.Wait();
	
	TRACER << "counting_to_20000000_with_2_threads_detach_test:" << g_number << '\n';
    ASSERT_THAT(g_number != 2 * COUNTING);
END_TEST


BEGIN_TEST(counting_to_10000000_with_thread_cancel_test) 
	g_number = 0;

	Thread thread(SharedPtr<IAction>(new ThreadAction()));
	
	thread.Cancel();
	
	TRACER << "counting_to_10000000_with_thread_cancel_test:" << g_number << '\n';
    ASSERT_THAT(g_number != COUNTING);
END_TEST

BEGIN_SUITE(thread tests)
    TEST(counting_to_20000000_with_2_threads_join_test)
    TEST(counting_to_20000000_with_2_threads_join_async_test)
    TEST(counting_to_20000000_with_2_threads_detach_test)
    TEST(counting_to_10000000_with_thread_cancel_test)
END_SUITE
