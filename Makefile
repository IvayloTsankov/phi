# Set up basic variables:

CC = g++
CFLAGS = -c -Wall -DSLOGGING -std=c++11
LDFLAGS =

CFLAGS += $(shell pkg-config --cflags libpng)
CFLAGS += -Ithird_party/

LDFLAGS += $(shell pkg-config --libs libpng)

# check for debug
ifeq ($1, "debug")
	CFLAGS += -g
endif

#  # List of sources:
SOURCES = src/main.cpp src/pngwrapper.cpp
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = phi

  
all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
  
clean:
	rm $(OBJECTS) $(EXECUTABLE)
