CC=g++
CFLAGS=-Wall -g
LDFLAGS=-g
MAINSOURCE=main.cpp
SOURCES=Set.cpp List.cpp Edge.cpp Vertices.cpp
HEADERS=$(SOURCES:.cpp=.h)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE) $(HEADERS) $(MAINSOURCE)
	
$(EXECUTABLE): $(OBJECTS) $(MAINSOURCE)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MAINSOURCE) -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@