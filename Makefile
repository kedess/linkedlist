CC=gcc
CFLAGS = -c -o3 -Wall -std=c11 -fPIC

SOURCES=src/linkedlist.c

OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = liblinkedlist

all: create_required_dirs $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -shared -o build/liblinkedlist.so $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(OBJECTS)
	
create_required_dirs:
	@if [ ! -d build ]; then mkdir build; fi

install:
	cp build/liblinkedlist.so /usr/lib/
	@if [ ! -d /usr/include/linkedlist ]; then mkdir /usr/include/linkedlist; fi
	cp -r src/linkedlist.h /usr/include/linkedlist/linkedlist.h
	ldconfig
