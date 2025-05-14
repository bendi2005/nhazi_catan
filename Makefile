# === CONFIG ===
CXX := g++
CXXFLAGS := -Wall -DMEMTRACE # -Werror

SRC_DIRS := . include src 
OBJ_DIR := obj
BIN_DIR := bin
TARGET := $(BIN_DIR)/onitama.exe

# === FILES ===
SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# === RULES ===

all: $(TARGET)
	cloc core.cpp src include

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

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
