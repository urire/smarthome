#ifndef THREAD_POOL_NOOP_COMMAND_HPP
#define THREAD_POOL_NOOP_COMMAND_HPP

#include "command.hpp"		// experis::Command

namespace experis {

class NoopCommand : public Command {
public:
	// NoopCommand() = default;
	// ~NoopCommand() = default;
	
	virtual void Do();

};

} // experis

#endif	// THREAD_POOL_NOOP_COMMAND_HPP
