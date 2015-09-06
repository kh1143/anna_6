CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES= main.cpp \
		 file.cpp \
		 list.cpp \
		 huffman.cpp \
		 tree.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= huffman

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(PROGRAMS) *.o core
	@rm -f $(EXECUTABLE)
