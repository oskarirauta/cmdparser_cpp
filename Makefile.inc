CMDPARSER_DIR?=./cmdparser
INCLUDES += -I$(CMDPARSER_DIR)/include
CMDPARSER_OBJS:= \
	objs/cmdparser.o

objs/cmdparser.o: $(CMDPARSER_DIR)/src/cmdparser.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
