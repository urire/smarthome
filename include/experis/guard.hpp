#ifndef EXPERIS_GUARD_HPP
#define EXPERIS_GUARD_HPP

#include "mutex.hpp"		// experis::Mutex
#include "iuncopyable.hpp"	// experis::IUncopyable

namespace experis {

class Guard : private IUncopyable {
public:
	// Guard() = delete;
	
	Guard(Mutex& a_lock);
	~Guard();

private:
	Mutex& m_lock;

};

} // experis

#endif	// EXPERIS_GUARD_HPP
