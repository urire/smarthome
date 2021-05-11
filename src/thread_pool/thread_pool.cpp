#include "thread_pool.hpp"			// experis::ThreadPool
#include "exit_looper.hpp"			// experis::ExitLooper
#include "noop_command.hpp"			// experis::NoopCommand

namespace experis {

ThreadPool::ThreadPool(size_t a_numThreads)
: IUncopyable()
, m_commands()
, m_activeThreads(a_numThreads)
, m_loopers(m_activeThreads, SharedPtr<IAction>(new TPLooper(m_commands)))
, m_cv()
, m_mtx()
, m_randPoint(m_mtx, m_cv)
, m_isAlive(true)
, m_pool(m_randPoint)
, m_joiner(new JoinAction(m_pool, m_isAlive, m_randPoint))
, m_unblocker(0)
, m_blocker(new Blocker(m_unblocker)) {		
	m_pool.AddJoiner(m_joiner);
	
	for(size_t i = 0; i < m_loopers.size(); ++i) {
		m_pool.Add(m_loopers[i]);
	}
}

ThreadPool::~ThreadPool() {		
	m_isAlive.Clear();
	m_randPoint.Notify();
	for(size_t i = 0; i < m_activeThreads; ++i) {
		m_commands.Enqueue(SharedPtr<Command>(new ExitLooper()));
	}	
}

void ThreadPool::Add(const SharedPtr<Command>& a_cmd) {
	m_commands.Enqueue(a_cmd);
}

void ThreadPool::Pause() {		
	for(size_t i = 0; i < m_activeThreads; ++i) {
		m_commands.Enqueue(m_blocker);
	}
}

void ThreadPool::Resume() {
	for(size_t i = 0 ; i < m_activeThreads ; ++i) {
		m_unblocker.Post();
	}
}

void ThreadPool::IncThreads() {
	++m_activeThreads;
	m_loopers.push_back(SharedPtr<IAction>(new TPLooper(m_commands)));		
	m_pool.Add(m_loopers.back());		
	m_unblocker.Post();
}

void ThreadPool::DecThreads() {
	if(0 == m_activeThreads) {
		throw DecreaseWithZeroThreadsException();
	}
	
	SharedPtr<Command> noopCmd = SharedPtr<Command>(new NoopCommand());
	
	--m_activeThreads;
	
	for(size_t i = 0; i < m_activeThreads; ++i) {
		m_commands.Enqueue(noopCmd);
	}
	
	m_commands.Enqueue(SharedPtr<Command>(new ExitLooper()));		
	m_unblocker.Wait();
}

size_t ThreadPool::ActiveThreads() const {
	return m_activeThreads;
}

} // experis
