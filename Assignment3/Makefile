CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

#List of source files
SOURCES = functions.c main.c 

#List of object files to be generated
OBJECTS = $(SOURCES:.c=.o)

#Executable file name
EXECUTABLE = main

#Default target
all: $(EXECUTABLE)

#Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Specify dependencies explicitly
main.o: main.c functions.h
functions.o: functions.c functions.h

# Clean up intermediate object files and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)