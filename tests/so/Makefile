# this is my target
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
TARGET1 = libsensor4.so
TARGET2 = libsensor5.so
TARGET3 = libcontroller1.so
TARGET4 = libcontroller2.so

# General compilation flags

# The compiler will be g++("CXX" is MAKE variable)
CXX = g++

# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -g3 -ansi -pedantic -fPIC -Wall -Werror
CXXFLAGS = $(CFLAGS) -std=c++03 $(CPPFLAGS)

# Include directory
INC_DIR = ../../include
SRC_DIR = ../../src
EXPERIS_INC_DIR = $(INC_DIR)/experis
SMART_HOME_INC_DIR = $(INC_DIR)/smart_home

CPPFLAGS := -I$(EXPERIS_INC_DIR) -I$(SMART_HOME_INC_DIR)
CPPFLAGS += -I$(SRC_DIR)

# All .c files in this directory are my sources
SOURCES = agent.cpp agent_details.cpp sensor.cpp controller.cpp mediator.cpp publisher.cpp subscriber.cpp extractor.cpp distributor.cpp event.cpp event_type.cpp location.cpp timestamp.cpp logger.cpp multi_threaded_handler.cpp atomic.cpp rendezvous_point.cpp mutex.cpp guard.cpp semaphore.cpp condition_variable.cpp thread.cpp thread_pool.cpp blocker.cpp tp_looper.cpp pool.cpp old_thread.cpp completion_aware_thread.cpp join_action.cpp exit_looper.cpp noop_command.cpp   

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.cpp=.o)

# The default command, compile all the sources
$(TARGET1): $(OBJECTS) sensor4.o
	$(CXX) -pthread -shared -o $(TARGET1) $(OBJECTS) sensor4.o

$(TARGET2): $(OBJECTS) sensor5.o
	$(CXX) -pthread -shared -o $(TARGET2) $(OBJECTS) sensor5.o

$(TARGET3): $(OBJECTS) controller1.o
	$(CXX) -pthread -shared -o $(TARGET3) $(OBJECTS) controller1.o

$(TARGET4): $(OBJECTS) controller2.o
	$(CXX) -pthread -shared -o $(TARGET4) $(OBJECTS) controller2.o
	
agent.o:  $(SRC_DIR)/agent/agent.cpp $(SMART_HOME_INC_DIR)/agent.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/agent/agent.cpp
	
agent_details.o:  $(SRC_DIR)/agent/agent_details.cpp $(SMART_HOME_INC_DIR)/agent_details.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/agent/agent_details.cpp
	
sensor.o:  $(SRC_DIR)/sensor/sensor.cpp $(SMART_HOME_INC_DIR)/sensor.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/sensor/sensor.cpp
	
controller.o:  $(SRC_DIR)/controller/controller.cpp $(SMART_HOME_INC_DIR)/controller.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/controller/controller.cpp

mediator.o:  $(SRC_DIR)/mediator/mediator.cpp $(SMART_HOME_INC_DIR)/mediator.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/mediator/mediator.cpp
	
publisher.o:  $(SRC_DIR)/publisher/publisher.cpp $(SMART_HOME_INC_DIR)/publisher.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/publisher/publisher.cpp
	
subscriber.o:  $(SRC_DIR)/subscriber/subscriber.cpp $(SMART_HOME_INC_DIR)/subscriber.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/subscriber/subscriber.cpp
	
extractor.o:  $(SRC_DIR)/extractor/extractor.cpp $(SMART_HOME_INC_DIR)/extractor.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/extractor/extractor.cpp
	
distributor.o:  $(SRC_DIR)/distributor/distributor.cpp $(SMART_HOME_INC_DIR)/distributor.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/distributor/distributor.cpp
	
event.o:  $(SRC_DIR)/event/event.cpp $(SMART_HOME_INC_DIR)/event.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/event/event.cpp
	
event_type.o:  $(SRC_DIR)/event/event_type.cpp $(SMART_HOME_INC_DIR)/event_type.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/event/event_type.cpp
	
location.o:  $(SRC_DIR)/location/location.cpp $(SMART_HOME_INC_DIR)/location.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/location/location.cpp
	
timestamp.o:  $(SRC_DIR)/timestamp/timestamp.cpp $(SMART_HOME_INC_DIR)/timestamp.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/timestamp/timestamp.cpp
	
logger.o:  $(SRC_DIR)/logger/logger.cpp $(SMART_HOME_INC_DIR)/logger.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/logger/logger.cpp
	
multi_threaded_handler.o:  $(SRC_DIR)/multi_threaded_handler/multi_threaded_handler.cpp $(SMART_HOME_INC_DIR)/multi_threaded_handler.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/multi_threaded_handler/multi_threaded_handler.cpp
	
sensor1.o:  ../test_agents/sensor1.cpp ../test_agents/sensor1.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/sensor1.cpp

sensor2.o:  ../test_agents/sensor2.cpp ../test_agents/sensor2.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/sensor2.cpp
	
sensor3.o:  ../test_agents/sensor3.cpp ../test_agents/sensor3.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/sensor3.cpp	
	
sensor4.o:  ../test_agents/sensor4.cpp ../test_agents/sensor4.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/sensor4.cpp	
		
sensor5.o:  ../test_agents/sensor5.cpp ../test_agents/sensor5.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/sensor5.cpp	
	
controller1.o:  ../test_agents/controller1.cpp ../test_agents/controller1.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/controller1.cpp	

controller2.o:  ../test_agents/controller2.cpp ../test_agents/controller2.hpp
	$(CXX) $(CXXFLAGS) -c ../test_agents/controller2.cpp	
	
atomic.o:  $(SRC_DIR)/atomic/atomic.cpp $(EXPERIS_INC_DIR)/atomic.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/atomic/atomic.cpp
	
rendezvous_point.o:  $(SRC_DIR)/rendezvous_point/rendezvous_point.cpp $(EXPERIS_INC_DIR)/rendezvous_point.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/rendezvous_point/rendezvous_point.cpp
	
mutex.o:  $(SRC_DIR)/mutex/mutex.cpp $(EXPERIS_INC_DIR)/mutex.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/mutex/mutex.cpp
	
guard.o:  $(SRC_DIR)/guard/guard.cpp $(EXPERIS_INC_DIR)/guard.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/guard/guard.cpp
	
semaphore.o:  $(SRC_DIR)/semaphore/semaphore.cpp $(EXPERIS_INC_DIR)/semaphore.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/semaphore/semaphore.cpp
	
condition_variable.o:  $(SRC_DIR)/condition_variable/condition_variable.cpp $(EXPERIS_INC_DIR)/condition_variable.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/condition_variable/condition_variable.cpp
	
thread.o:  $(SRC_DIR)/thread/thread.cpp $(EXPERIS_INC_DIR)/thread.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread/thread.cpp
	
thread_pool.o:  $(SRC_DIR)/thread_pool/thread_pool.cpp $(EXPERIS_INC_DIR)/thread_pool.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/thread_pool.cpp
	
blocker.o:  $(SRC_DIR)/thread_pool/blocker.cpp $(EXPERIS_INC_DIR)/blocker.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/blocker.cpp
	
tp_looper.o:  $(SRC_DIR)/thread_pool/tp_looper.cpp $(EXPERIS_INC_DIR)/tp_looper.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/tp_looper.cpp
	
pool.o:  $(SRC_DIR)/pool/pool.cpp $(EXPERIS_INC_DIR)/pool.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/pool/pool.cpp
	
old_thread.o:  $(SRC_DIR)/old_thread/old_thread.cpp $(EXPERIS_INC_DIR)/old_thread.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/old_thread/old_thread.cpp
	
completion_aware_thread.o:  $(SRC_DIR)/old_thread/completion_aware_thread.cpp $(EXPERIS_INC_DIR)/completion_aware_thread.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/old_thread/completion_aware_thread.cpp
	
join_action.o:  $(SRC_DIR)/thread_pool/join_action.cpp $(EXPERIS_INC_DIR)/join_action.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/join_action.cpp
		
exit_looper.o:  $(SRC_DIR)/thread_pool/exit_looper.cpp $(EXPERIS_INC_DIR)/exit_looper.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/exit_looper.cpp
			
noop_command.o:  $(SRC_DIR)/thread_pool/noop_command.cpp $(EXPERIS_INC_DIR)/noop_command.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/thread_pool/noop_command.cpp
	
clean:
	$(RM) *.o *.so
	
check: clean $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

