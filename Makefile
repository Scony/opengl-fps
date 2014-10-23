LIBS=-lGL -lglut -lGLEW -lGLU
CC=g++

SOURCES=main.cpp Bar.cpp Window.cpp Camera.cpp
HEADERS=Bar.h Window.h Camera.h
OBJECTS=$(SOURCES:.cpp=.o)

all: main.out

main.out: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

clean:
	-rm -f *.o *~ *.out
