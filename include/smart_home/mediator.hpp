#ifndef SABATO_MEDIATOR_HPP
#define SABATO_MEDIATOR_HPP

#include "publisher.hpp"		// smart_home::Publisher
#include "subscriber.hpp"		// smart_home::Subscriber
#include "logger.hpp"      		// smart_home::Logger
#include "iuncopyable.hpp"		// experis::IUncopyable
#include "shared_ptr.hpp"		// experis::SharedPtr

using namespace experis;

namespace smart_home {

class Mediator : private IUncopyable {
public:
	typedef SharedPtr<Logger> LoggerPtr;
	typedef SharedPtr<IPublisher> PublisherPtr;
	typedef SharedPtr<ISubscriber> SubscriberPtr;

	friend class Agent;
	friend class Sensor;
	friend class Controller;
	friend class CentralHub;

public:
	// Mediator() = delete;
	// ~Mediator() = default;

	Mediator(const PublisherPtr& a_publisher, const SubscriberPtr& a_subscriber);

private: // for friends
	void SetLogger(const LoggerPtr& a_logger);

	const LoggerPtr& GetLogger();
	const PublisherPtr& GetPublisher();
	const SubscriberPtr& GetSubscriber();

private:
	PublisherPtr m_publisher;
	SubscriberPtr m_subscriber;
	LoggerPtr m_logger;

};

} // smart_home

#endif	// SABATO_MEDIATOR_HPP
