CXX = g++
CXXFLAGS = -Wall -g -std=c++11
TARGET = baseball_simulator 
SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.dep)
RM = rm -f

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.dep:%.cpp
	$(SHELL) -c '$(CXX) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(TARGET) $(DEPS) $(OBJS)
