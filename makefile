CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lncurses -lcurl -lcw
SOURCES= main.cpp statusbar.cpp hardware.cpp getdata.cpp say_pico.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=run
HEADERS= 

all: $(SOURCES) $(EXECUTABLE) $(HEADERS)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o: 
	$(CC) $(CFLAGS) $< -o $@
	
clean :
	rm *.o

