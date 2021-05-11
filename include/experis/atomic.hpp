#ifndef EXPERIS_ATOMIC_HPP
#define EXPERIS_ATOMIC_HPP

#include <stddef.h>		// size_t

namespace experis {

template<typename T>
class Atomic {
public:
	// ~Atomic() = default;

	Atomic();	
	Atomic(const Atomic& a_other);

	Atomic& operator=(const Atomic& a_other);	
	Atomic& operator++();	
	Atomic& operator--();	
	
	operator T () const;

private:
	static const size_t s_bitsInByte;

private:
	T m_counter;
	
};

} // experis

#include "inl/atomic.inl"

#endif	// EXPERIS_ATOMIC_HPP
