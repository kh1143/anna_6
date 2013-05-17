CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES= main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= hw6

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(PROGRAMS) *.o core
	@rm -f $(EXECUTABLE)