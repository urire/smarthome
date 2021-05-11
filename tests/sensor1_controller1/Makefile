CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g
CFLAGS += -pthread
# c++
CXXFLAGS = $(CFLAGS) -std=c++03 
# c pre processor
CPPFLAGS += -I$(INC_DIR_SMART_HOME) -I$(INC_DIR_EXPERIS)
LDLIBS = -lpthread -ldl
LDFLAGS = 

INC_DIR_EXPERIS = ../../include/experis
INC_DIR_SMART_HOME = ../../include/smart_home
SRC_DIR = ../../src

SOURCES_NEEDED = central_hub/central_hub.cpp extractor/extractor.cpp distributor/distributor.cpp agent/agent.cpp agent/agent_details.cpp agent/agent_factory.cpp sensor/sensor.cpp controller/controller.cpp event/event.cpp event/event_type.cpp location/location.cpp timestamp/timestamp.cpp publisher/publisher.cpp subscriber/subscriber.cpp thread/thread.cpp mutex/mutex.cpp guard/guard.cpp semaphore/semaphore.cpp condition_variable/condition_variable.cpp atomic/atomic.cpp rendezvous_point/rendezvous_point.cpp configurator/configurator.cpp location/location.cpp mediator/mediator.cpp logger/logger.cpp thread_pool/thread_pool.cpp thread_pool/blocker.cpp thread_pool/tp_looper.cpp pool/pool.cpp old_thread/old_thread.cpp old_thread/completion_aware_thread.cpp thread_pool/join_action.cpp thread_pool/exit_looper.cpp thread_pool/noop_command.cpp multi_threaded_handler/multi_threaded_handler.cpp


# add private source for this target
SOURCES_MINE = sensor1_controller1_mu_test.cpp 
TARGET = sensor1_controller1_mu_test

# what are these
# =
# :=
# ?=

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(SOURCES_MINE)
OBJECTS := $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)	

all : $(TARGET)

run:  $(TARGET)
	 ./$(TARGET)

check: clean run
grind: valgrind helgrind
valgrind: #memory leak
	valgrind --tool=drd -v --log-file=logdrd01.txt ./$(TARGET)
helgrind:  #race conditions  
	valgrind --tool=helgrind -v --log-file=loghelgrind01.txt ./$(TARGET)
	
clean:
	$(RM) $(TARGET) $(OBJECTS)


.PHONY: all clean run check grind valgrind helgrind 




