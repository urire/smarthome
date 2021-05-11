#include "mediator.hpp"		// smart_home::Mediator

namespace smart_home {

Mediator::Mediator(const PublisherPtr& a_publisher, const SubscriberPtr& a_subscriber) 
: m_publisher(a_publisher)
, m_subscriber(a_subscriber)
, m_logger()
{
}

void Mediator::SetLogger(const LoggerPtr& a_logger) {
	m_logger = a_logger;
}

const Mediator::LoggerPtr& Mediator::GetLogger() {
	return m_logger;
}

const Mediator::PublisherPtr& Mediator::GetPublisher() {
	return m_publisher;
}

const Mediator::SubscriberPtr& Mediator::GetSubscriber() {
	return m_subscriber;
}

} //smart_home
