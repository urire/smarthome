#ifndef THREAD_POOL_BLOCKER_HPP
#define THREAD_POOL_BLOCKER_HPP

#include "command.hpp"			// experis::Command
#include "semaphore.hpp"		// experis::Semaphore

namespace experis {

class Blocker : public Command {
public:
	// ~Blocker() = default;
	
	Blocker(Semaphore& a_blockedItems);
	
	virtual void Do();

private:
	Semaphore& m_blockedItems;

};

} // experis

#endif	// THREAD_POOL_BLOCKER_HPP
