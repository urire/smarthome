#ifndef SABATO_IPUBLISHER_HPP
#define SABATO_IPUBLISHER_HPP

#include "event.hpp"			// smart_home::Event
#include "iuncopyable.hpp"		// experis::IUncopyable
#include "shared_ptr.hpp"		// experis::SharedPtr

using namespace experis;

namespace smart_home {

struct IPublisher : private IUncopyable {
public:
	// Publisher() = default;

    virtual ~IPublisher() {}
	
	virtual void Publish(const SharedPtr<Event>& a_event) = 0;
	
};

} // smart_home

#endif	// SABATO_IPUBLISHER_HPP
