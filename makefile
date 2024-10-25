# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Target executable name
TARGET = main

# Source files
SRCS = main.cpp queue.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to compile the program
all: $(TARGET)

# Rule to link the object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile the source files into object files
%.o: %.cpp queue.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the entire project
rebuild: clean all
