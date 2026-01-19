CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I.
LIBS = -lcheck -lsubunit -lm -lpthread -lrt

SRC_DIR = s21_decimal
TEST_DIR = s21_test
BUILD_DIR = build
COV_REPORT_DIR = coverage_report

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%_test.o, $(TEST_FILES))

TEST_BIN = $(BUILD_DIR)/tests

.PHONY: all test clean gcov_report coverage help

all: test

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(SRC_OBJS) $(TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)


coverage: clean
	$(MAKE) gcov_report

gcov_report: clean
	@mkdir -p $(BUILD_DIR)
	$(eval COV_CFLAGS := $(CFLAGS) -fprofile-arcs -ftest-coverage)

	@$(foreach src,$(SRC_FILES), \
		$(CC) $(COV_CFLAGS) -c $(src) -o $(BUILD_DIR)/$(notdir $(src:.c=.o)) &&) true

	@$(foreach test,$(TEST_FILES), \
		$(CC) $(COV_CFLAGS) -c $(test) -o $(BUILD_DIR)/$(notdir $(test:.c=_test.o)) &&) true

	$(CC) $(COV_CFLAGS) $(BUILD_DIR)/*.o -o $(TEST_BIN) $(LIBS)

	./$(TEST_BIN)

	lcov --capture --directory $(BUILD_DIR) --output-file coverage.info -q
	genhtml coverage.info --output-directory $(COV_REPORT_DIR)
	@echo "Coverage report generated in $(COV_REPORT_DIR)/index.html"

clean:
	rm -rf $(BUILD_DIR) coverage.info $(COV_REPORT_DIR)

help:
	@echo "Available targets:"
	@echo "  make           – build and run tests"
	@echo "  make test      – run tests"
	@echo "  make gcov_report – generate HTML coverage report"
	@echo "  make clean     – remove build artifacts"