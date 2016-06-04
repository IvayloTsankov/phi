# Set up basic variables:

CC = g++
CFLAGS = -O3 -fopenmp -ftree-vectorize -c -Wall -DSLOGGING -DSLOGGING_DEBUG -std=c++11 -msse2
LDFLAGS =

CFLAGS += $(shell pkg-config --cflags libpng sdl)
CFLAGS += -Ithird_party/

LDFLAGS += $(shell pkg-config --libs libpng sdl)
LDFLAGS += -lpthread -ljpeg -fopenmp -msse2

# check for debug
ifeq ($1, "debug")
	CFLAGS += -g
endif

#  # List of sources:
SOURCES = src/main.cpp src/pngwrapper.cpp src/sdl.cpp src/utils.cpp src/image.cpp \
			src/effects.cpp src/userinput.cpp src/inputhandler.cpp src/scale.cpp \
			src/jpegwrapper.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = phi

  
all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
  
clean:
	rm $(OBJECTS) $(EXECUTABLE)
