CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lcheck -lsubunit -lm -lpthread -lrt

SRC_DIR = s21_decimal
HELPER_DIR = s21_helper
TEST_DIR = s21_decimal_test
BUILD_DIR = build
COV_REPORT_DIR = gcov_report

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
HELPER_FILES := $(wildcard $(HELPER_DIR)/*.c)

LIB_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/$(SRC_DIR)/%.o,$(SRC_FILES))
LIB_OBJS += $(patsubst $(HELPER_DIR)/%.c,$(BUILD_DIR)/$(HELPER_DIR)/%.o,$(HELPER_FILES))

LIB_GCOV_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/$(SRC_DIR)/%.gcov.o,$(SRC_FILES))
LIB_GCOV_OBJS += $(patsubst $(HELPER_DIR)/%.c,$(BUILD_DIR)/$(HELPER_DIR)/%.gcov.o,$(HELPER_FILES))

TEST_SOURCES := $(filter-out $(TEST_DIR)/s21_test_main.c, $(wildcard $(TEST_DIR)/*.c))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/$(TEST_DIR)/%.o,$(TEST_SOURCES))
TEST_GCOV_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/$(TEST_DIR)/%.gcov.o,$(TEST_SOURCES))

TEST_MAIN := $(TEST_DIR)/s21_test_main.c

TEST_BIN := $(BUILD_DIR)/tests
TEST_GCOV_BIN := $(BUILD_DIR)/tests_gcov

.PHONY: all clean test gcov_report

all: test

$(BUILD_DIR)/%.o: %.c s21_decimal.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.gcov.o: %.c s21_decimal.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_MAIN) $(TEST_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_GCOV_BIN): $(TEST_MAIN) $(TEST_GCOV_OBJS) $(LIB_GCOV_OBJS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o $@ $(LIBS)

gcov_report: $(TEST_GCOV_BIN)
	./$(TEST_GCOV_BIN)
	lcov --capture --directory $(BUILD_DIR) --output-file coverage.info -q
	genhtml coverage.info --output-directory $(COV_REPORT_DIR)
	@echo "Coverage report: $(COV_REPORT_DIR)/index.html"

clean:
	rm -rf $(BUILD_DIR) coverage.info $(COV_REPORT_DIR)