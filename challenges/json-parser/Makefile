# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# File names
TARGET = json-parser
SOURCE = $(TARGET).cpp

# Build targets
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean build files
clean:
	rm -f $(TARGET)

# Debug build with additional flags
debug: CXXFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

# Release build with optimization
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

.PHONY: all clean debug release
