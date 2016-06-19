CXX = g++

CXXFLAGS = -Os -Wall -std=c++11 -Wparentheses -pthread

SRCS = Edge.cpp Node.cpp Graph.cpp main.cpp GraphAlgorithms.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = HY583_GraphAlgorithmsProjectExecutable

.PHONY: depend clean

all:	$(MAIN)
	@echo  Programm has been compiled

$(MAIN):	$(OBJS) 
		$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend:	$(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
