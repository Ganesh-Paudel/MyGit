# Variables for compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lcrypto -lz

# The name of your final executable
TARGET = myGit

# List of object files (the .o files generated from your .c files)
OBJS = main.o commands.o util.o objectStore.o

# The default rule: build the target
all: $(TARGET)

# Rule to link the object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the project directory
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf sandbox/

test: $(TARGET)
	mkdir -p sandbox
	mv $(TARGET) sandbox/
	@echo "Binary copied to sandbox. Ready to test!"
