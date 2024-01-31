CXX := emcc
SRC_DIR := .
INCLUDE_DIR := include
BUILD_DIR := build
TARGET := main.html

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

CXXFLAGS := -I$(INCLUDE_DIR) --std=c++20 -sUSE_SDL=2 -O2

LDFLAGS := -sALLOW_MEMORY_GROWTH=1 -sASYNCIFY -sASSERTIONS --embed-file images@/images

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
