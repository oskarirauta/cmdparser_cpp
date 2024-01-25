all: world
CXX?=g++
CXXFLAGS?=--std=c++17 -Wall
LDFLAGS?=-L/lib -L/usr/lib

INCLUDES+= -I./include

OBJS:= \
	objs/main.o

CMDPARSER_DIR:=.
include Makefile.inc

world: example

$(shell mkdir -p objs)

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

example: $(CMDPARSER_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@;

clean:
	@rm -rf objs example
