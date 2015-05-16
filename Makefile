#	PA4 - Event Simulation
#	George Karapanagos
#	Makefile

CXXFLAGS =	-m32 -g -Wall -fmessage-length=0

OBJS =		CustomerLine.o EventQueue.o qSim.o

LIBS =      

TARGET =	qSim

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

*.o: *.cpp
	$(CXX) -c $(CXXFLAGS) *.cpp

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.exe
