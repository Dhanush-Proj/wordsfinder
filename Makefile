# Define the compiler
CC = gcc

# Define compiler flags (e.g., -Wall for warnings, -g for debug info)
CFLAGS = -Wall -g

# Define the executable name
TARGET = wfind

# Define the source file
SRC = wfind.c

# Default target: builds the executable
all: $(TARGET)

# Rule to build the executable from the source file
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean target: removes generated files
clean:
	rm -f $(TARGET)
