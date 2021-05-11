#include "atomic.hpp"		// experis::Atomic

namespace experis {

Atomic<bool>::Atomic(bool a_value)
: m_value(a_value) 
{
}	

Atomic<bool>::Atomic(const Atomic& a_other)
: m_value(a_other.m_value) 
{
}

Atomic<bool>& Atomic<bool>::operator=(const Atomic& a_other) {
	m_value = a_other.m_value;
	
	return *this;
}

bool Atomic<bool>::operator!() const {
	return m_value == false;
}

Atomic<bool>::operator bool () const {
	return m_value;
}

void Atomic<bool>::Set() {
	__sync_fetch_and_or(&m_value, 1);
}

void Atomic<bool>::Clear() {
	__sync_fetch_and_and(&m_value, 0);
}

} // experis
