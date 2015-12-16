CC = gcc
CXX=g++
RM=rm -f
TARGET = campaign
CPPFLAGS = -std=c++11 -O0 -g3 -Wall -c
LDFLAGS = -std=c++11 -g3 
LDLIBS=$(shell root-config --libs)

SRCS=CampTargeter.cpp main.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: campaign

campaign: $(OBJS)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) -o campaign $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
