#include "extractor.hpp"

namespace smart_home {

Extractor::ExtractAction::ExtractAction(Extractor& a_this) 
: m_this(a_this) 
{
}

void Extractor::ExtractAction::Perform() { 
	m_this.startExtracting(); 
}

size_t Extractor::s_threadAmount = 7;

Extractor::Extractor(EventQueue& a_events) 
: IUncopyable()
, m_pool(s_threadAmount)
, m_events(a_events)
, m_distributor()
, m_notifier(1)
, m_action(ActionPtr(new ExtractAction(*this)))
, m_thread()
, m_shutting(false)
{
}

Extractor::~Extractor() {
    Shutdown();
}

void Extractor::Add(const EventType& a_type, const HandlerPtr& a_handle) {
	m_distributor.Add(a_type, a_handle);
}

void Extractor::Remove(const HandlerPtr& a_handle) {
	m_distributor.Remove(a_handle);
}

void Extractor::Start() {
    m_thread = ThreadPtr(new Thread(m_action));
}

void Extractor::Shutdown() {
    if(m_shutting == false) {
		m_shutting.Set();
		m_events.AsyncShutdown();
		m_thread->Join();
	}
}

void Extractor::startExtracting() {
    EventPtr event;
	
	while(!m_shutting) {
		m_events.Dequeue(event);
		m_notifier.Wait();
		m_pool.Add(SharedPtr<Command>(new Distributor::DistributeCommand(m_distributor, m_notifier, event)));
	}
}

} // smart_home
