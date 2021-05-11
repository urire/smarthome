#ifndef EXPERIS_SHARED_PTR_HPP
#define EXPERIS_SHARED_PTR_HPP

#include "atomic.hpp"		// experis::Atomic
#include <exception>		// std::exceptions
#include <cstddef>			// size_t, NULL

namespace experis {

template<typename T, typename RefCounter = Atomic<size_t> >
class SharedPtr {
public:
	struct NullPointerException : public std::exception {};

public:
	explicit SharedPtr(T* a_ptr = NULL);
	SharedPtr(const SharedPtr& a_other);	
	~SharedPtr();

	SharedPtr& operator=(const SharedPtr& a_other);
	bool operator<(const SharedPtr& a_other) const;
	T& operator*() const;
	T* operator->() const;
	operator T* () const;

	template<typename S>
	SharedPtr(SharedPtr<S, RefCounter>& a_other);
	
	template<typename S>
	S* StaticCast();
	
	const RefCounter& Counter() const;
	bool IsNull() const;
	
private:
	void construct();
	void incRefCount();
	void decRefCount();	
	
private:
	T* m_ptr;
	RefCounter* m_counter;
	
};

} // experis

#include "inl/shared_ptr.inl"

#endif	// EXPERIS_SHARED_PTR_HPP
