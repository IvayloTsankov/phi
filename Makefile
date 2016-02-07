# Set up basic variables:

CC = g++
CFLAGS = -c -Wall -DSLOGGING -std=c++11 -g
LDFLAGS =

CFLAGS += $(shell pkg-config --cflags libpng sdl)
CFLAGS += -Ithird_party/

LDFLAGS += $(shell pkg-config --libs libpng sdl)

# check for debug
ifeq ($1, "debug")
	CFLAGS += -g
endif

#  # List of sources:
SOURCES = src/main.cpp src/pngwrapper.cpp src/sdl.cpp src/utils.cpp src/image.cpp
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = phi

  
all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
  
clean:
	rm $(OBJECTS) $(EXECUTABLE)
