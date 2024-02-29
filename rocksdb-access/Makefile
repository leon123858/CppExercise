CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2
LDFLAGS=-lrocksdb

SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=myprogram

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
