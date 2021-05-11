#include "mu_test.h"

#include "event.hpp"
#include "extractor.hpp"
#include "event_type.hpp"
#include "shared_ptr.hpp"
#include "ievent_handler.hpp"

using namespace smart_home;
using namespace experis;

static int g_number1 = 0;
static int g_number2 = 0;

struct MyHandler1 : public IEventHandler {
    virtual void Handle(const SharedPtr<Event>& a_event) { ++g_number1; }
};

struct MyHandler2 : public IEventHandler {
    virtual void Handle(const SharedPtr<Event>& a_event) { ++g_number2; }
};

BEGIN_TEST(extractor_test) 
	Extractor router;

	EventType e1("*", "2", "2");
	EventType e2("2", "2", "2");
	EventType e3("3", "2", "2");
	EventType e4("3", "2", "3");
	
	SharedPtr<Event> event = SharedPtr<Event>(new Event(e4));
	
	Extractor::Container handles1;
	Extractor::Container handles2;
	Extractor::Container handles3;

	SharedPtr<IEventHandler> handler1 = SharedPtr<IEventHandler>(new MyHandler1());
	SharedPtr<IEventHandler> handler2 = SharedPtr<IEventHandler>(new MyHandler2());

	router.Add(e1, handler1);
	router.Add(e2, handler2);

	router.Get(e2, handles2);
	router.Get(e3, handles1);
	router.Get(e4, handles3);
	
	handles2[0]->Handle(event);
	handles2[1]->Handle(event);
	
	bool passed = handles2.size() == 2 && handles1.size() == 1 && handles3.size() == 0 && g_number1 == 1 && g_number2 == 1;

	TRACER << "extractor_test: " << passed << '\n';
    ASSERT_THAT(passed);
END_TEST

BEGIN_SUITE(extractor tests)
    TEST(extractor_test)
END_SUITE
