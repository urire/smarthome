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

SOURCES_NEEDED = thread_pool/thread_pool.cpp thread_pool/blocker.cpp thread_pool/tp_looper.cpp pool/pool.cpp mutex/mutex.cpp rendezvous_point/rendezvous_point.cpp old_thread/old_thread.cpp semaphore/semaphore.cpp guard/guard.cpp condition_variable/condition_variable.cpp old_thread/completion_aware_thread.cpp thread_pool/join_action.cpp thread_pool/exit_looper.cpp thread_pool/noop_command.cpp atomic/atomic.cpp
# add private source for this target
SOURCES_MINE = thread_pool_test.cpp 
TARGET = thread_pool_test

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




	
