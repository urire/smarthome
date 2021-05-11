#include "mu_test.h"

#include "central_hub.hpp"		// smart_home::CentralHub
#include "logger.hpp"			// smart_home::Logger
#include "definitions.hpp"		// CONTROLLER1_EVENT_TYPE, CONTROLLER1_LOGGER
#include "shared_ptr.hpp"		// experis::SharedPtr
#include <string>				// std::string
#include <map>					// std::map
#include <unistd.h>				// sleep

using namespace experis;
using namespace smart_home;

BEGIN_TEST(simulation) 
	std::map<std::string, SharedPtr<Logger> > loggers;	
	std::string message;

	{
		CentralHub hub("./config.ini");
			
		hub.Start();
		
		sleep(13);
		
		
		loggers = hub.GetLoggers();	
		message = loggers["hvac_log"]->Message();
		
		hub.Shutdown();
	}

	TRACER << message << '\n';
    ASSERT_PASS();
END_TEST

BEGIN_SUITE(simulation tests)
    TEST(simulation)
END_SUITE
