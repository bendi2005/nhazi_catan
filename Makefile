# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target program name
TARGET = my_program

# Source files (all .cpp files in the root directory)
SOURCES = $(wildcard *.cpp)

# Object files (all .cpp files converted to .o files)
OBJECTS = $(SOURCES:.cpp=.o)

# Include directories (Add paths if you have custom header directories)
INCLUDES = -I.

# Default rule: build the target (executable)
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS)

# Rule to compile each .cpp file into .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove old object files and executable
clean:
	rm -f $(TARGET) $(OBJECTS)

# Optional: Clean all object files inside the obj/ directory
clean_objs:
	rm -f obj/*.o
