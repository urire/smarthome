#ifndef THREAD_POOL_EXIT_LOOPER_HPP
#define THREAD_POOL_EXIT_LOOPER_HPP

#include "command.hpp"						// experis::Command
#include "completion_aware_thread.hpp"		// experis::CompletionAwareThread

namespace experis {

class ExitLooper : public Command {
public:
	// ExitLooper() = default;
	// ~ExitLooper() = default;
	
	virtual void Do();

};

} // experis

#endif	// THREAD_POOL_EXIT_LOOPER_HPP
