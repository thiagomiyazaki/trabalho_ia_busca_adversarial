# Define the compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -Wextra -O2

# Define the name of the executable output
TARGET = main 

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c alpha_beta_pruning.c alpha_beta_pruning.h board.c board.h execution.c execution.h minimax.c minimax.h

# Clean up
clean:
	rm -f $(TARGET)

