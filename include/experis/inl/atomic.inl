#ifndef EXPERIS_ATOMIC_INL
#define EXPERIS_ATOMIC_INL

#include <assert.h>		// assert

namespace experis {

template<>
class Atomic<bool> {
public:
	Atomic(bool a_value = false);	
	Atomic(const Atomic& a_other);
	Atomic& operator=(const Atomic& a_other);
	
	bool operator!() const;
	operator bool () const;
	
	void Set();
	void Clear();
	
private:
	char m_value;
	
};

template<typename T>
const size_t Atomic<T>::s_bitsInByte = 8;

template<typename T>
Atomic<T>::Atomic()
: m_counter(1) 
{
	assert(sizeof(m_counter) <= s_bitsInByte);
}

template<typename T>
Atomic<T>::Atomic(const Atomic& a_other)
: m_counter(a_other.m_counter) 
{
}

template<typename T>
Atomic<T>& Atomic<T>::operator=(const Atomic& a_other) {
	m_counter = a_other.m_counter;
	
	return *this;
}	

template<typename T>
Atomic<T>& Atomic<T>::operator++() {
	__sync_fetch_and_add(&m_counter, 1);	

	return *this;
}

template<typename T>
Atomic<T>& Atomic<T>::operator--() {
	__sync_fetch_and_sub(&m_counter, 1);	

	return *this;
}

template<typename T>
Atomic<T>::operator T () const {
	return m_counter;
}

} // experis

#endif	// EXPERIS_ATOMIC_INL
