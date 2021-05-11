CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g
CFLAGS += -pthread
# c++
CXXFLAGS = $(CFLAGS) -std=c++03 
# c pre processor
CPPFLAGS += -I$(INC_DIR_SMART_HOME) -I$(INC_DIR_EXPERIS)
LDLIBS = -lpthread
LDFLAGS = -pthread

INC_DIR_EXPERIS = ../../include/experis
INC_DIR_SMART_HOME = ../../include/smart_home
SRC_DIR = ../../src

SOURCES_NEEDED = extractor/extractor.cpp distributor/distributor.cpp event/event.cpp event/event_type.cpp location/location.cpp semaphore/semaphore.cpp atomic/atomic.cpp timestamp/timestamp.cpp thread_pool/thread_pool.cpp thread_pool/blocker.cpp thread_pool/tp_looper.cpp pool/pool.cpp old_thread/old_thread.cpp old_thread/completion_aware_thread.cpp thread_pool/join_action.cpp thread_pool/exit_looper.cpp thread_pool/noop_command.cpp multi_threaded_handler/multi_threaded_handler.cpp
# add private source for this target
SOURCES_MINE = extractor_test.cpp 
TARGET = extractor_test

# what are these
# = assignement
# := 
# ?=

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(SOURCES_MINE)
OBJECTS := $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)	
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

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




	
