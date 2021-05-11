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

BEGIN_TEST(sensor1_controller1__test) 
	std::string message;

	{
		CentralHub hub("./config.ini");
			
		hub.Start();
		
		sleep(1);

		hub.LoggerMessage(CONTROLLER1_LOGGER, message);
		hub.Shutdown();	
	}

    ASSERT_THAT(message == "test\ntest\n");
END_TEST

BEGIN_SUITE(thread tests)
    TEST(sensor1_controller1__test)
END_SUITE
