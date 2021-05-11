#ifndef EXPERIS_SEMAPHORE_HPP
#define EXPERIS_SEMAPHORE_HPP

#include "iunassignable.hpp"	// experis::IUnassignable
#include <exception>			// std::exception
#include <semaphore.h>			// sem_t

namespace experis {

class Semaphore : private IUnassignable {
public:	
	struct ValueOutOfRangeException : public std::exception {};
	struct SignalInterruptException : public std::exception {};
	struct OverflowException : public std::exception {};
	
public:
	// Semaphore() = delete;

	Semaphore(size_t a_size);
	Semaphore(const Semaphore& a_other);				
	~Semaphore();
	
	void Wait();	
	void Post();

private:
	sem_t m_semaphore;															

};

} // experis

#endif	// EXPERIS_SEMAPHORE_HPP
