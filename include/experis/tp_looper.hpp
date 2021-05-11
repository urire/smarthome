#ifndef THREAD_POOL_TP_LOOPER_HPP
#define THREAD_POOL_TP_LOOPER_HPP

#include "thread_safe_queue.hpp"	// experis::ThreadSafeQueue
#include "shared_ptr.hpp"			// experis::SharedPtr
#include "iaction.hpp"				// experis::IAction
#include "command.hpp"				// experis::Command

namespace experis {

class TPLooper : public IAction {	
public:
	TPLooper(ThreadSafeQueue<SharedPtr<Command> >& a_commands);
	
	virtual void Perform();		

private:
	ThreadSafeQueue<SharedPtr<Command> >& m_commands;	

};

} // experis

#endif	// THREAD_POOL_TP_LOOPER_HPP
