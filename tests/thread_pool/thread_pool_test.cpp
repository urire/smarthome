#include "mu_test.h"

#include "thread_pool.hpp"		// experis::ThreadPool, experis::Command
#include <unistd.h>				// sleep, usleep
#include <iostream>				// std::cout, std::endl
#include <string>				// std:string

using namespace experis;

class TestCommand : public Command {
public:
	TestCommand(bool& a_flag) : m_flag(a_flag) {}
	
	virtual void Do() {
		sleep(2);
    
		m_flag = true;
	}
	
private:
	bool& m_flag;
	
};

class IncCommand : public Command {
public:
	IncCommand(int& a_number, Mutex& a_mtx) : m_number(a_number), m_mtx(a_mtx) {}
	
	virtual void Do() {
		
		m_mtx.Lock();
		usleep(10);
		++m_number;
		m_mtx.UnLock();
	}
	
private:
	int& m_number;
	Mutex& m_mtx;
	
};

int g_number = 0;
Mutex g_mtx;

BEGIN_TEST(thread_pool_bool_test) 
	bool arr[4] = { false };	
	ThreadPool tb(2);

	tb.Add(SharedPtr<Command>(new TestCommand(arr[0])));
	tb.Add(SharedPtr<Command>(new TestCommand(arr[1])));
	tb.Add(SharedPtr<Command>(new TestCommand(arr[2])));
	tb.Add(SharedPtr<Command>(new TestCommand(arr[3])));
	
	sleep(3);
	
	bool passed = arr[0] && arr[1] && !arr[2] && !arr[3];
	
	TRACER << "thread_pool_bool_test:" << passed << '\n';
    ASSERT_THAT(passed);
END_TEST

BEGIN_TEST(thread_pool_no_tasks_exit_test) 
	{
		ThreadPool tb(2);
		
		sleep(1);
	}
	
	TRACER << "thread_pool_bool_test:" << true << '\n';
    ASSERT_PASS();
END_TEST

BEGIN_TEST(thread_pool_add_test) 
	SharedPtr<Command> ptr = SharedPtr<Command>(new IncCommand(g_number, g_mtx));	
	g_number = 0;
	
	{	
		ThreadPool tb(3);

		for(size_t i = 0 ; i < 10000 ; ++i) {		
			tb.Add(ptr);
		}
	}

	bool passed = 10000 == g_number;
	TRACER << "thread_pool_bool_test:" << passed << '\n';
    ASSERT_THAT(passed);
END_TEST

BEGIN_SUITE(thread pool tests)
    TEST(thread_pool_bool_test)
    TEST(thread_pool_no_tasks_exit_test)
    TEST(thread_pool_add_test)
END_SUITE
