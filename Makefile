# === CONFIG ===
SFML_DIR := SFML-3.0.0
SFML_INCLUDE := -I$(SFML_DIR)/include
SFML_LIB := -L$(SFML_DIR)/lib
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

CXX := g++
CXXFLAGS := -Wall -DMEMTRACE $(SFML_INCLUDE) -g # Added -g for debug symbols
LDFLAGS := $(SFML_LIB) $(SFML_LIBS)

SRC_DIRS := . include src 
OBJ_DIR := obj
BIN_DIR := bin
TARGET := $(BIN_DIR)/catan

# === FILES ===
SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# === RULES ===

all: $(TARGET)
	cloc core.cpp src include

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)


# === VALGRIND TARGETS ===
valgrind: $(TARGET)
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         --verbose \
	         --log-file=valgrind-out.txt \
	         --error-exitcode=1 \
	         ./$(TARGET) $(ARGS)
	@echo "Valgrind output saved to valgrind-out.txt"

# For stuck programs - adds timeout and shows progress
valgrind-timeout: $(TARGET)
	timeout 30s valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         --verbose \
	         --log-file=valgrind-out.txt \
	         --error-exitcode=1 \
	         ./$(TARGET) $(ARGS) || \
	         (echo "Program timed out or failed"; exit 0)
	@echo "Valgrind output saved to valgrind-out.txt"

# Quick check without full details
valgrind-quick: $(TARGET)
	valgrind --leak-check=summary \
	         --show-leak-kinds=definite \
	         --log-file=valgrind-quick.txt \
	         ./$(TARGET) $(ARGS)
	@echo "Quick check output saved to valgrind-quick.txt"

# === DEBUGGING HELPERS ===
# Run with gdb for debugging hangs
debug-hang: $(TARGET)
	gdb -ex run --args ./$(TARGET) $(ARGS)

# Run with strace to see system calls
strace: $(TARGET)
	strace -f -o strace-out.txt ./$(TARGET) $(ARGS)
