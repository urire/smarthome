#ifndef SABATO_DISTRIBUTOR_HPP
#define SABATO_DISTRIBUTOR_HPP

#include <vector>					    // std::vector
#include <map>						    // std::map
#include <set>						    // std::set
#include "event.hpp"				    // smart_home::Event
#include "event_type.hpp"			    // smart_home::EventType
#include "multi_threaded_handler.hpp"   // smart_home::MultiThreadedHandler
#include "iuncopyable.hpp"			    // experis::IUncopyable
#include "command.hpp"			        // experis::Command
#include "shared_ptr.hpp"       	    // experis::SharedPtr
#include "semaphore.hpp"                // experis::Semaphore
#include "lookup_table.hpp"             // experis::LookupTable          

using namespace experis;

namespace smart_home {

class Distributor : private IUncopyable {
public:
    typedef SharedPtr<Event> EventPtr;
	typedef SharedPtr<MultiThreadedHandler> HandlerPtr;
	typedef std::set<HandlerPtr> HandlerSet;
	typedef std::vector<HandlerPtr> HandlerContainer;
	typedef std::map<EventType, HandlerSet> HandlerMap;
    typedef LookupTable<std::string, Semaphore> HandlerLUT;

    class DistributeCommand : public Command {
    public:
        DistributeCommand(Distributor& a_this, Semaphore& a_notifier, const EventPtr& a_event);
        
        virtual void Do();
        
    private:
        Distributor& m_this;
        Semaphore& m_notifier;
        EventPtr m_event;
        
    };

public:
    Distributor();
    ~Distributor();

    void Distribute(const EventPtr& a_event, Semaphore& a_notifier); 
    void Add(const EventType& a_type, const HandlerPtr& a_handle);
	void Remove(const HandlerPtr& a_handle); 

private:
    void listen(HandlerContainer& a_listeners, const EventType& a_type);
	void addListener(HandlerContainer& a_listeners, const EventType& a_type);
    void wait(HandlerContainer& a_listeners, Semaphore& a_notifier);
    void notify(HandlerContainer& a_listeners, const EventPtr& a_event);

private:
    HandlerMap m_router;
    HandlerLUT m_typeCounters;

};

} // smart_home

#endif	// SABATO_DISTRIBUTOR_HPP
