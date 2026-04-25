CC = g++
CFLAGS = -g -Wall -Wextra -O3 -std=c++17

# Source files
EXTRA_SRC := ../source/board.cpp
TEST_SRC := $(wildcard *_test.cpp)

# Output test binary
TARGET = runTests

# GoogleTest flags (system install)
GTEST_LIBS = -lgtest -lgtest_main -pthread

all: $(TARGET)

$(TARGET): $(TEST_SRC) $(EXTRA_SRC)
	@echo "Building GoogleTest binary..."
	$(CC) $(CFLAGS) $^ -o $@ $(GTEST_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)