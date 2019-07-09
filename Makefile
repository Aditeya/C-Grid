CC = gcc

# DEBUG Flags
CFLAGS = -g3 -ggdb -Wall
# COMPILE flags
#CFLAGS = -Wall -O3

LIBS = `sdl2-config --libs --cflags`

TARGET = main

$(TARGET):$(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)
