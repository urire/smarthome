#ifndef EXPERIS_SHARED_PTR_INL
#define EXPERIS_SHARED_PTR_INL

namespace experis {

template<typename T, typename RefCounter>
SharedPtr<T, RefCounter>::SharedPtr(T* a_ptr)
: m_ptr(a_ptr)
, m_counter(NULL) 
{
	construct();
}

template<typename T, typename RefCounter>
SharedPtr<T, RefCounter>::SharedPtr(const SharedPtr& a_other)
: m_ptr(a_other.m_ptr)
, m_counter(a_other.m_counter) 
{
	incRefCount();
}

template <typename T, typename RefCounter>
SharedPtr<T, RefCounter>& SharedPtr<T, RefCounter>::operator=(const SharedPtr& a_other) {
	if (this != &a_other) {
		decRefCount();
		m_ptr = a_other.m_ptr;
		m_counter = a_other.m_counter;
		incRefCount();
	}

	return *this;
}

template <typename T, typename RefCounter>
bool SharedPtr<T, RefCounter>::operator<(const SharedPtr& a_other) const {
	return m_ptr < a_other.m_ptr;
}

template <typename T, typename RefCounter>
SharedPtr<T, RefCounter>::~SharedPtr() {
	decRefCount();
}

template<typename T, typename RefCounter>
T& SharedPtr<T, RefCounter>::operator*() const {
	if (!m_ptr) {
		throw NullPointerException();
	}

	return *m_ptr;
}

template<typename T, typename RefCounter>
T* SharedPtr<T, RefCounter>::operator->() const {
	return m_ptr;
}

template<typename T, typename RefCounter>
SharedPtr<T, RefCounter>::operator T*() const {
	return m_ptr;
}

template <typename T, typename RefCounter>
template <typename S>
SharedPtr<T, RefCounter>::SharedPtr(SharedPtr<S, RefCounter>& a_other)
: m_ptr(&(*a_other))
, m_counter(&const_cast<RefCounter&>(a_other.Counter())) 
{
	incRefCount();
}

template <typename T, typename RefCounter>
template<typename S>
S* SharedPtr<T, RefCounter>::StaticCast() {
	return dynamic_cast<S*>(m_ptr);
}

template<typename T, typename RefCounter>
const RefCounter& SharedPtr<T, RefCounter>::Counter() const {
	if (!m_counter) {
		throw NullPointerException();
	}

	return *m_counter;
}

template<typename T, typename RefCounter>
bool SharedPtr<T, RefCounter>::IsNull() const {
	return m_ptr == NULL;
}

template <typename T, typename RefCounter>
void SharedPtr<T, RefCounter>::construct() {
	if (m_ptr) {
		try {
			m_counter = new RefCounter();
		}
		catch (...) {
			delete m_ptr;
			throw;
		}
	}
}

template <typename T, typename RefCounter>
void SharedPtr<T, RefCounter>::incRefCount() {
	if (m_counter) {
		++(*m_counter);
	}
}

template <typename T, typename RefCounter>
void SharedPtr<T, RefCounter>::decRefCount() {
	if (m_counter) {
		--(*m_counter);
		if (!(*m_counter)) {
			delete m_ptr;
			delete m_counter;
		}
	}
}

} // experis

#endif	// EXPERIS_SHARED_PTR_INL
