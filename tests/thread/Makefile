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

SOURCES_NEEDED = thread/thread.cpp guard/guard.cpp mutex/mutex.cpp rendezvous_point/rendezvous_point.cpp atomic/atomic.cpp condition_variable/condition_variable.cpp
# add private source for this target
SOURCES_MINE = thread_test.cpp 
TARGET = thread_test

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




	
