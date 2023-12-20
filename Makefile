CC := gcc
CFLAGS := -Wall -Wextra -g
BUILD_DIR := build

LIB_SOURCES := src/rdsp.c src/generator.c src/stream.c src/util.c
LIB_OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(LIB_SOURCES))
LIB_ONLY_NAME := librdsp.a
LIB_NAME := $(BUILD_DIR)/$(LIB_ONLY_NAME)

TEST_SOURCES := test/test.c
TEST_OBJECTS := $(patsubst test/%.c,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
TEST_EXECUTABLE := $(BUILD_DIR)/dsp

EXTERNAL_LIBS := -pthread -lm
all: $(LIB_NAME) $(TEST_EXECUTABLE)

run: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(LIB_NAME): $(LIB_OBJECTS)
	ar rcs $@ $^

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $^ -L$(BUILD_DIR) -l:$(LIB_ONLY_NAME) $(EXTERNAL_LIBS)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o  $@ $< -Iinclude $(EXTERNAL_LIBS)

$(BUILD_DIR)/%.o: test/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -Iinclude

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

format:
	clang-format -i src/* include/* test/*

.PHONY: all clean format

