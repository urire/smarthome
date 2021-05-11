#include "mu_test.h"

#include "thread_safe_queue.hpp"		// experis::ThreadSafeQueue
#include "thread.hpp"					// experis::Thread, experis::IAction
#include <iostream>
#include <vector>
#include <ctime>

#define N 100000

using namespace experis;

struct Producer : public IAction {	
	Producer(ThreadSafeQueue<int>& a_queue) : m_queue(a_queue) {}
	
	virtual void Perform() { 
		for(int i = 0; i < N; ++i) {
			m_queue.Enqueue(i);
		}
	}
	
private:
	ThreadSafeQueue<int>& m_queue;

};

struct Consumer : public IAction {	
	Consumer(ThreadSafeQueue<int>& a_queue) : m_queue(a_queue), m_value(-1) {}
	
	virtual void Perform() { 
		int value;
		for(int i = 0; i < N; ++i) {
			m_queue.Dequeue(value);
			
			m_value = value;
		}
	}
	
private:
	ThreadSafeQueue<int>& m_queue;
	int m_value;
};

struct Producer2 : public IAction {	
	Producer2(ThreadSafeQueue<int>& a_queue, size_t a_begin, size_t a_end) : m_queue(a_queue), m_begin(a_begin), m_end(a_end) {} 
	
	virtual void Perform() { 
		for(size_t i = m_begin; i < m_end; ++i) {
			m_queue.Enqueue(i);
		}
	}
	
private:
	ThreadSafeQueue<int>& m_queue;
	size_t m_begin;
	size_t m_end;

};

struct Consumer2 : public IAction {	
	Consumer2(ThreadSafeQueue<int>& a_queue, int a_size) : m_queue(a_queue), m_size(a_size), m_expected1(0), m_expected2(m_size) {} 
	
	virtual void Perform() { 
			int value;
		for(int i = 0; i < m_size * 2; ++i) {
			m_queue.Dequeue(value);
			
			if(value == m_expected1) {
				++m_expected1;
			}
			else if(value == m_expected2) {
				++m_expected2;			
			}
		}
	}
	
private:
	ThreadSafeQueue<int>& m_queue;
	int m_size;
	int m_expected1;
	int m_expected2;

};

struct Producer3 : public IAction {	
	Producer3(ThreadSafeQueue<std::pair<int, time_t> >& a_queue, size_t a_begin, size_t a_end) : m_queue(a_queue), m_begin(a_begin), m_end(a_end) {} 
	
	virtual void Perform() { 
		time_t now;
		
		for(size_t i = m_begin; i < m_end; ++i) {
			time(&now);
			m_queue.Enqueue(std::pair<int, time_t>(i, now));
		}
	}
	
private:
	ThreadSafeQueue<std::pair<int, time_t> >& m_queue;
	size_t m_begin;
	size_t m_end;

};

struct Consumer3 : public IAction {	
	Consumer3(ThreadSafeQueue<std::pair<int, time_t> >& a_queue, int a_size
		, std::vector<std::pair<int, time_t> >& a_first, std::vector<std::pair<int, time_t> >& a_second) 
	: m_queue(a_queue)
	, m_size(a_size) 
	, m_first(a_first)
	, m_second(a_second)
	{
	} 
	
	virtual void Perform() { 
		for(int i = 0; i < m_size; ++i) {
			std::pair<int, time_t> value;
			m_queue.Dequeue(value);

			if(value.first < m_size) {
				m_first.push_back(value);
			}
			else {
				m_second.push_back(value);			
			}
		}
	}
	
private:
	ThreadSafeQueue<std::pair<int, time_t> >& m_queue;
	int m_size;
	std::vector<std::pair<int, time_t> >& m_first;
	std::vector<std::pair<int, time_t> >& m_second;

};

BEGIN_TEST(thread_safe_queue_producer_test) 
	ThreadSafeQueue<int> queue(N);
	
	for(size_t i = 0; i < N; ++i) {
		queue.Enqueue(i);
	}
	
	int value;
	
	for(size_t i = 0; i < N; ++i) {
		queue.Dequeue(value);
		
		TRACER << "thread_safe_queue_producer_test passed:" << (value == (int)i) << '\n';
    	ASSERT_THAT(value == (int)i);
	}
	
	queue.AwaitShutdown();
	
	ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_safe_queue_producer_consumer_test) 
	ThreadSafeQueue<int> queue;
	
	Thread producerThread(SharedPtr<IAction>(new Producer(queue)));
	Thread consumerThread(SharedPtr<IAction>(new Consumer(queue)));
	
	producerThread.Join();
	consumerThread.Join();
	
	queue.AwaitShutdown();

	ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_safe_queue_2producer_consumer_test) 
	ThreadSafeQueue<int> queue;
	
	Thread producer1Thread(SharedPtr<IAction>(new Producer2(queue, 0 , N)));
	Thread producer2Thread(SharedPtr<IAction>(new Producer2(queue, N , 2 * N)));
	Thread consumerThread(SharedPtr<IAction>(new Consumer2(queue, N)));

	producer1Thread.Join();
	producer2Thread.Join();
	consumerThread.Join();
	
	queue.AwaitShutdown();
	
	ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_safe_queue_2producer_2consumer_test) 
	std::vector<std::pair<int, time_t> > first1;
	std::vector<std::pair<int, time_t> > first2;
	std::vector<std::pair<int, time_t> > second1;
	std::vector<std::pair<int, time_t> > second2;
	
	{
		ThreadSafeQueue<std::pair<int, time_t> > queue;
		
		Thread producer1Thread(SharedPtr<IAction>(new Producer3(queue, 0, N)));
		Thread producer2Thread(SharedPtr<IAction>(new Producer3(queue, N, 2 * N)));
		Thread consumer1Thread(SharedPtr<IAction>(new Consumer3(queue, N, first1, second1)));
		Thread consumer2Thread(SharedPtr<IAction>(new Consumer3(queue, N, first2, second2)));
		
		producer1Thread.Join();
		producer2Thread.Join();
		consumer1Thread.Join();
		consumer2Thread.Join();
		
		queue.AwaitShutdown();
	}
	
	int expected1 = 0;
	int expected2 = N;
	int idx1 = 0;
	int idx2 = 0;
	int idx21 = 0;
	int idx22 = 0;
	
	time_t lastTime;
	time_t lastTime2;
	
	for(int i = 0; i < 2 * N; ++i) {
		if(first1[idx1].first == expected1) {
			if(idx1 && first1[idx1].second < lastTime) {
    			ASSERT_FAIL("thread_safe_queue_producer_consumer_test failed");

				break;
			}

			lastTime = first1[idx1].second;
			++idx1;
			++expected1;
		}
		else if(first2[idx2].first == expected1) {
			if(idx2 && first2[idx2].second < lastTime) {
				ASSERT_FAIL("thread_safe_queue_producer_consumer_test failed");

				break;
			}
			
			lastTime2 = first2[idx2].second;
			++idx2;
			++expected1;
		}
		else if(second1[idx21].first == expected2){
			if(idx21 && second1[idx21].second < lastTime2) {
				ASSERT_FAIL("thread_safe_queue_producer_consumer_test failed");

				break;
			}
			
			lastTime2 = second1[idx21].second;
			++idx21;
			++expected2;
		}
		else if(second2[idx22].first == expected2) {
			if(idx22 && second2[idx22].second < lastTime2) {
				ASSERT_FAIL("thread_safe_queue_producer_consumer_test failed");

				break;
			}
			
			lastTime2 = second2[idx22].second;
			++idx22;
			++expected2;
		}
		else {
			ASSERT_FAIL("thread_safe_queue_producer_consumer_test failed");

			break;
		}	
	}

	
	ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_safe_queue_is_full_test) 
	ThreadSafeQueue<int> queue(100);
	
	for(size_t i = 0; i < 101; ++i) {
		
		
		if(i == 100) {
			TRACER << "thread_safe_queue_is_full_test passed:" << (queue.IsFull()) << '\n';
    		ASSERT_THAT(queue.IsFull());
    		queue.Dequeue();
		}
		
		queue.Enqueue(i);
	}
	
	int value;
	
	for(size_t i = 0; i < 100; ++i) {
		queue.Dequeue(value);
		
		TRACER << "thread_safe_queue_is_full_test passed:" << (value == (int)i) << '\n';
    	ASSERT_THAT(value - 1 == (int)i);
	}
	
	queue.AwaitShutdown();
	
	ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_safe_queue_is_empty_test) 
	ThreadSafeQueue<int> queue(100);
	
	TRACER << "thread_safe_queue_is_empty_test passed:" << (queue.IsEmpty()) << '\n';
    ASSERT_THAT(queue.IsEmpty());
	
	for(size_t i = 0; i < 100; ++i) {		
		queue.Enqueue(i);
	}
	
	int value;
	
	for(size_t i = 0; i < 100; ++i) {
		queue.Dequeue(value);
	}
	
	TRACER << "thread_safe_queue_is_empty_test passed:" << (queue.IsEmpty()) << '\n';
    ASSERT_THAT(queue.IsEmpty());
    
    queue.AwaitShutdown();
END_TEST

BEGIN_TEST(thread_safe_queue_size_test) 
	ThreadSafeQueue<int> queue(100);
	
	TRACER << "thread_safe_queue_size_test passed:" << (queue.Size() == 0) << '\n';
    ASSERT_THAT(queue.Size() == 0);
	
	for(size_t i = 0; i < 100; ++i) {		
		queue.Enqueue(i);
	}
	
	TRACER << "thread_safe_queue_size_test passed:" << (queue.Size() == 100) << '\n';
    ASSERT_THAT(queue.Size() == 100);
	
	int value;
	
	for(size_t i = 0; i < 100; ++i) {
		queue.Dequeue(value);
	}
	
	TRACER << "thread_safe_queue_size_test passed:" << (queue.Size() == 0) << '\n';
    ASSERT_THAT(queue.Size() == 0);
    
    queue.AwaitShutdown();
END_TEST

BEGIN_TEST(thread_safe_queue_clear_test) 
	ThreadSafeQueue<int> queue(100);

    ASSERT_THAT(queue.Size() == 0);
	
	for(size_t i = 0; i < 100; ++i) {		
		queue.Enqueue(i);
	}

    ASSERT_THAT(queue.Size() == 100);
	
	queue.Clear();
	
	TRACER << "thread_safe_queue_clear_test passed:" << (queue.Size() == 0) << '\n';
    ASSERT_THAT(queue.Size() == 0);
    
    queue.AwaitShutdown();
END_TEST

BEGIN_TEST(thread_safe_queue_size_zero_test) 
	try{
		ThreadSafeQueue<int> queue(0);
	}
	catch(const ThreadSafeQueue<int>::ContainerSizeIsZeroException& ex) {
		ASSERT_PASS();
	}

    ASSERT_PASS();
END_TEST

BEGIN_SUITE(thread safe queue tests)
    TEST(thread_safe_queue_producer_test)
    TEST(thread_safe_queue_producer_consumer_test)
    TEST(thread_safe_queue_2producer_consumer_test)
    TEST(thread_safe_queue_2producer_2consumer_test)
    TEST(thread_safe_queue_is_full_test)
    TEST(thread_safe_queue_is_empty_test)
    TEST(thread_safe_queue_size_test)
    TEST(thread_safe_queue_clear_test)
    TEST(thread_safe_queue_size_zero_test)
END_SUITE
