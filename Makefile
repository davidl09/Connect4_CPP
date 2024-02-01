CXX := g++#emcc
SRC_DIR := .
INCLUDE_DIR := include
BUILD_DIR := build
TARGET := main

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

CXXFLAGS := -I$(INCLUDE_DIR) --std=c++23 -Og -fext-numeric-literals#-sUSE_SDL=2

LDFLAGS := -lSDL2 -ltbb#-sALLOW_MEMORY_GROWTH=1 -sASSERTIONS --embed-file images@/images -fexceptions

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(SRC) -o $@ $(CXXFLAGS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
