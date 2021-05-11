#ifndef THREAD_POOL_COMMAND_HPP
#define THREAD_POOL_COMMAND_HPP

#include "iunassignable.hpp"		// experis::IUnassignable

namespace experis {

class Command : private IUnassignable {
public:
	// Command() = default;

	virtual ~Command() {}
	virtual void Do() = 0;

};

} // experis

#endif	// THREAD_POOL_COMMAND_HPP
