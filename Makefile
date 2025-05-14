# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -MMD -MP

# Files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

# Target
TARGET := my_program

# Default rule
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp into .o with dependency files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

# Include auto-generated dependency files
-include $(DEPS)

.PHONY: all clean
