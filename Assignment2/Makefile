#Created with the help of ChatGPT
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# List of source files
SRCS = OF.c functions.c GA.c

# Generate the list of object files by replacing .c with .o in source files
OBJS = $(SRCS:.c=.o)

# Name of the executable
EXECUTABLE = GA

all: $(EXECUTABLE)

# Rule to build the executable by linking object files
$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXECUTABLE)