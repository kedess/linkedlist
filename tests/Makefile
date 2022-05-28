CC=gcc
CFLAGS = -c -o3 -Wall -std=c11

LIBS=-llinkedlist

SOURCES=src/test.c

OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test

all: create_required_dirs $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o build/test $(OBJECTS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(OBJECTS)

create_required_dirs:
	@if [ ! -d build ]; then mkdir build; fi