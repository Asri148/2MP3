CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm

# List of source files
SOURCES = OF.c functions.c GA.c 

# List of object files to be generated
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = GA

# Default target
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Clean up intermediate object files and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
